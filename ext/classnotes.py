
# -*- coding: utf-8 -*-

import sphinx
from docutils import nodes
from docutils.parsers.rst import directives

class activitat(nodes.General, nodes.Element):
    tema = None

class exercici(activitat):
    name = "Exercici"
    css_class = "exercici"
    
class problema(activitat):
    name = "Problema"
    css_class = "problema"

class solucio(activitat): 
    name = "Solucio"
    css_class = "solucio"

# activitat

def activitat_visitor(klass):
    def _visitor(self, node):
        def _a(s):
            self.body.append(s)
        _a('<div class="%s">' % klass.css_class)
        _a('<p class="first %s-title">%s %s</p>' % 
           (klass.css_class, klass.name, node['id']))
        _a('<div class="body">')
    return _visitor

def depart_activitat_html(self, node):
    self.body.append('</div></div>')

# exercici
visit_exercici_html = activitat_visitor(exercici)
depart_exercici_html = depart_activitat_html

def visit_exercici_latex(self, node):
    self.body.append('\\par\\vspace{3.0mm}\\hrule')
    self.body.append('\\makebox[-3mm][l]{}\\makebox[3mm][l]{$\\triangleright$}')
    self.body.append('\\begin{small}\\textbf{Exercici %s}\\quad' % node['id'])

def depart_exercici_latex(self, node):
    self.body.append('\\end{small}\\par\\vspace{2mm}\\hrule\\vspace{1.0mm}')

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

class SolucioDirective(Activity):
    has_content = True
    required_arguments = 0
    optional_arguments = 0
    option_spec = {}
    
    def run(self):
        return [] # TODO: implement

# Transforms

def number_activities(app, doctree):
    # Get 'tema' from a directive found in any point in the file
    env = app.builder.env
    tema = env.docname
    if hasattr(env, 'classnotes_tema'):
        tema = env.classnotes_tema

    def _number(klass):
        n = 1
        for node in doctree.traverse(klass):
            node['id'] = "%s.%d" % (tema, n)
            n += 1

    _number(exercici)
    _number(problema)

# Setup

def setup(app):
    app.add_node(exercici,
                 html=(visit_exercici_html, depart_exercici_html),
                 latex=(visit_exercici_latex, depart_exercici_latex))
    app.add_node(problema,
                 html=(visit_problema_html, depart_problema_html),
                 latex=(visit_problema_latex, depart_problema_latex))

    app.add_directive('problema', ProblemaDirective)
    app.add_directive('exercici', ExerciciDirective)
    app.add_directive('solucio',  SolucioDirective)
    app.add_directive('tema',     TemaDirective)

    app.connect('doctree-read', number_activities)


