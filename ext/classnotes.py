# -*- coding: utf-8 -*-

from docutils import nodes

class exercici(nodes.General, nodes.Element): pass
class problema(nodes.General, nodes.Element):  pass

# exercici
def visit_exercici_html(self, node):
    self.body.append('<div class="exercici">')
    self.body.append('<p class="first exercici-title">Exercici %d</p>' % node['num'])
    self.body.append('<div class="body">')

def depart_exercici_html(self, node):
    self.body.append('</div></div>')

def visit_exercici_latex(self, node):
    self.body.append('\\par\\vspace{3.0mm}\\hrule')
    self.body.append('\\makebox[-3mm][l]{}\\makebox[3mm][l]{$\\triangleright$}')
    self.body.append('\\begin{small}\\textbf{Exercici %d}\\quad' % node['num'])

def depart_exercici_latex(self, node):
    self.body.append('\\end{small}\\par\\vspace{2mm}\\hrule\\vspace{1.0mm}')

# problema
def visit_problema_html(self, node):
    self.body.append('<div class="problema">')
    self.body.append('<p class="first problema-title">Problema %d</p>' % node['num'])
    self.body.append('<div class="body">')

def depart_problema_html(self, node):
    self.body.append('</div></div>')

def visit_problema_latex(self, node):
    self.body.append('\\par\\textbf{Problema %d}' % node['num'])
    self.body.append('\\par')

def depart_problema_latex(self, node):
    self.body.append('\\par\\vspace{2mm}')

# cppfunc

def visit_cppfunc_html(self, node):
    pass

def depart_cppfunc_html(self, node):
    pass

def visit_problema_latex(self, node):
    pass

def depart_problema_latex(self, node):
    pass

# Directives

from sphinx.util.compat import Directive, make_admonition

prob_num = 1

class ProblemaDirective(Directive):
    has_content = True
    def run(self):
        P = problema()
        self.state.nested_parse(self.content, self.content_offset, P)
        return [P]

class ExerciciDirective(Directive):
    has_content = True
    def run(self):
        E = exercici()
        self.state.nested_parse(self.content, self.content_offset, E)
        return [E]


# Transforms

from docutils.transforms import Transform
import cppfunc

class Numeros(Transform):
    default_priority = 710 
    def apply(self):
        pnum = 1
        for node in self.document.traverse(problema):
            node['num'] = pnum
            pnum += 1
        enum = 1
        for node in self.document.traverse(exercici):
            node['num'] = enum
            enum += 1

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
    app.add_directive('cppfunc',  cppfunc.CppFuncDirective)

    app.add_transform(Numeros)


