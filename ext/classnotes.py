# -*- coding: utf-8 -*-

import sphinx
from docutils import nodes
from docutils.parsers.rst import directives

class exercici(nodes.General, nodes.Element): pass
class problema(nodes.General, nodes.Element):  pass

# exercici
def visit_exercici_html(self, node):
    self.body.append('<div class="exercici">')
    self.body.append('<p class="first exercici-title">Exercici %s</p>' % node['id'])
    self.body.append('<div class="body">')

def depart_exercici_html(self, node):
    self.body.append('</div></div>')

def visit_exercici_latex(self, node):
    self.body.append('\\par\\vspace{3.0mm}\\hrule')
    self.body.append('\\makebox[-3mm][l]{}\\makebox[3mm][l]{$\\triangleright$}')
    self.body.append('\\begin{small}\\textbf{Exercici %s}\\quad' % node['id'])

def depart_exercici_latex(self, node):
    self.body.append('\\end{small}\\par\\vspace{2mm}\\hrule\\vspace{1.0mm}')

# problema
def visit_problema_html(self, node):
    self.body.append('<div class="problema">')
    self.body.append('<p class="first problema-title">Problema %s</p>' % node['id'])
    self.body.append('<div class="body">')

def depart_problema_html(self, node):
    self.body.append('</div></div>')

def visit_problema_latex(self, node):
    self.body.append('\\par\\textbf{Problema %s}' % node['id'])
    self.body.append('\\par')

def depart_problema_latex(self, node):
    self.body.append('\\par\\vspace{2mm}')

# Directives

from sphinx.util.compat import Directive, make_admonition

class Activity(Directive):
    activity_class = None
    has_content = True

    # Hay que poner esto para que se guarde el tema?
    option_spec = {
        'tema': directives.unchanged,
    }

    def run(self):
        self.assert_has_content()
        env = self.state.document.settings.env
        A = self.activity_class()
        tema = env.docname
        if hasattr(env, 'tema'):
            tema = env.tema
        A['tema'] = tema
        self.state.nested_parse(self.content, self.content_offset, A)
        return [A]

class ProblemaDirective(Activity):
    has_content = True
    activity_class = problema

class ExerciciDirective(Activity):
    has_content = True
    activity_class = exercici


class TemaDirective(Directive):
    has_content = True
    def run(self):
        env = self.state.document.settings.env
        env.tema = self.content[0]
        return []

# Transforms

from docutils.transforms import Transform

def process_activities(app, doctree, docname):
    print "processing activities: ", docname
    env = app.builder.env

    def assign_ids(seq):
        idxs = {}
        for node in seq:
            tema = node['tema']
            num = 1
            if idxs.has_key(tema):
                num = idxs[tema]
            idxs[tema] = num + 1
            node['id'] = "%s.%d" % (node['tema'], num)

    assign_ids(doctree.traverse(problema))
    assign_ids(doctree.traverse(exercici))

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
    app.add_directive('tema', TemaDirective)
    # import cppfunc
    # app.add_directive('cppfunc',  cppfunc.CppFuncDirective)
    
    # app.add_transform(Activities)
    app.connect('doctree-resolved', process_activities)


