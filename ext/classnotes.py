
# -*- coding: utf-8 -*-

import sphinx
from docutils import nodes
from docutils.parsers.rst import directives

class activitat(nodes.General, nodes.Element):
    name = "Activitat"
    tema = None
    numbering = True
    def get_title(self, _id): 
        return self.name + ' ' + _id

class exercici(activitat):
    name = "Exercici"
    css_class = "boxed exercici"

class exemple(activitat):
    name = "Exemple"
    css_class = "boxed exemple"
    numbering = False
    
class problema(activitat):
    name = "Problema"
    css_class = "problema"

class solucio(activitat): 
    name = "Solucio"
    css_class = "solucio"
    def get_title(self, _id): 
        return _id
        

class solution_list(nodes.General, nodes.Element):
    pass

# activitat

def activitat_visitor(klass):
    def _visitor(self, node):
        def _a(s):
            self.body.append(s)
        _a('<div class="%s">' % klass.css_class)
        _id = ''
        if node.has_key('id') and klass.numbering:
            _id = ' ' + node['id']
        _a('<p class="first %s title">%s</p>' % 
           (klass.css_class, node.get_title(_id)))
        _a('<div class="body">')
    return _visitor

def depart_activitat_html(self, node):
    self.body.append('</div></div>')

## Exercici & Exemple

def visit_activity_latex(klass):
    def _visitor(self, node):
        def _a(s):
            self.body.append(s)
        _a('\\par\\vspace{3.0mm}\\hrule')
        _a('\\makebox[-3mm][l]{}\\makebox[3mm][l]{$\\triangleright$}')
        _id = ''
        if node.has_key('id') and klass.numbering:
            _id = ' ' + node['id']
        _a('\\begin{small}\\textbf{%s}\\quad' % node.get_title(_id))
    return _visitor

def depart_activity_latex(self, node):
    self.body.append('\\end{small}\\par\\vspace{2mm}\\hrule\\vspace{1.0mm}')


# exercici
visit_exercici_html = activitat_visitor(exercici)
depart_exercici_html = depart_activitat_html
visit_exercici_latex = visit_activity_latex(exercici)
depart_exercici_latex = depart_activity_latex

# exemple
visit_exemple_html = activitat_visitor(exemple)
depart_exemple_html = depart_activitat_html
visit_exemple_latex = visit_activity_latex(exemple)
depart_exemple_latex = depart_activity_latex

# solucio
visit_solucio_html = activitat_visitor(solucio)
depart_solucio_html = depart_activitat_html
visit_solucio_latex = visit_activity_latex(solucio)
depart_solucio_latex = depart_activity_latex

# problema
visit_problema_html = activitat_visitor(problema)
depart_problema_html = depart_activitat_html

def visit_problema_latex(self, node):
    self.body.append('\\par\\textbf{Problema %s}' % node['id'])
    self.body.append('\\par')

def depart_problema_latex(self, node):
    self.body.append('\\par\\vspace{2mm}')

# Directives

from sphinx.util.compat import Directive, make_admonition

class TemaDirective(Directive):
    has_content = False
    required_arguments = 1
    optional_arguments = 0
    final_argument_whitespace = False
    option_spec = {}

    def run(self):
        env = self.state.document.settings.env
        env.classnotes_tema = self.arguments[0].lower()
        return []

class Activity(Directive):
    activity_class = None
    has_content = True

    def run(self):
        self.assert_has_content()
        A = self.activity_class()
        self.state.nested_parse(self.content, self.content_offset, A)
        return [A]

class ProblemaDirective(Activity):
    activity_class = problema

class ExerciciDirective(Activity):
    activity_class = exercici

class ExempleDirective(Activity):
    activity_class = exemple

def get_tema(env):
    tema = env.docname
    if hasattr(env, 'classnotes_tema'):
        tema = env.classnotes_tema
    return tema

class SolucioDirective(Activity):
    has_content = True
    required_arguments = 0
    optional_arguments = 0
    option_spec = {}
    
    def run(self):
        # Read the node
        self.assert_has_content()
        S = solucio()
        self.state.nested_parse(self.content, self.content_offset, S)
        env = self.state.document.settings.env
        S['docname'] = env.docname
        return [S]

class SolutionListDirective(Directive):
    def run(self):
        return [solution_list('')]

# Transforms

def number_activities(app, doctree):
    # Get 'tema' from a directive found in any point in the file
    env = app.builder.env
    tema = get_tema(env)


    def _number(klass):
        n = 1
        for node in doctree.traverse(klass):
            _id = "%s.%d" % (tema, n)
            node['id'] = _id
            for subnode in node:
                if type(subnode) == solucio:
                    subnode['id'] = klass.name + ' ' + _id
            n += 1

    _number(exercici)
    _number(problema)

def collect_solutions(app, doctree):
    # Add to environment
    # (to be able to collect all solutions from all documents)
    env = app.builder.env
    if not hasattr(env, 'classnotes_solution_list'):
        env.classnotes_solution_list = []
    tema = get_tema(env)
    for node in doctree.traverse(solucio):
        if type(node.parent) in [exercici, problema]:
            node.parent.remove(node)
            node
            env.classnotes_solution_list.append(node)

def purge_solutions(app, env, docname):
    if not hasattr(env, 'classnotes_solution_list'):
        return
    env.classnotes_solution_list = [s for s in env.classnotes_solution_list
                                if s['docname'] != docname]

def fill_solution_list(app, doctree, fromdocname):
    env = app.builder.env
    for node in doctree.traverse(solution_list):
        content = []
        if hasattr(env, 'classnotes_solution_list'):
            for sol in env.classnotes_solution_list:
                content.append(sol)
        node.replace_self(content)

# Setup

def setup(app):
    app.add_node(exercici,
                 html=(visit_exercici_html, depart_exercici_html),
                 latex=(visit_exercici_latex, depart_exercici_latex))
    app.add_node(exemple,
                 html=(visit_exemple_html, depart_exemple_html),
                 latex=(visit_exemple_latex, depart_exemple_latex))
    app.add_node(solucio,
                 html=(visit_solucio_html, depart_solucio_html),
                 latex=(visit_solucio_latex, depart_solucio_latex))
    app.add_node(problema,
                 html=(visit_problema_html, depart_problema_html),
                 latex=(visit_problema_latex, depart_problema_latex))

    app.add_directive('tema',     TemaDirective)
    app.add_directive('problema', ProblemaDirective)
    app.add_directive('exercici', ExerciciDirective)
    app.add_directive('exemple',  ExempleDirective)
    app.add_directive('solucio',  SolucioDirective)
    app.add_directive('llista_solucions', SolutionListDirective)

    app.connect('doctree-read', number_activities)
    app.connect('doctree-read', collect_solutions)
    app.connect('env-purge-doc', purge_solutions)
    app.connect('doctree-resolved', fill_solution_list)


