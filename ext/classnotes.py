# -*- coding: utf-8 -*-

from docutils import nodes

class exercici(nodes.General, nodes.Element): pass
class problema(nodes.General, nodes.Element):  pass

def visit_exercici_html(self, node):
    self.body.append('<div class="exercici">')

def depart_exercici_html(self, node):
    self.body.append('</div>')

def visit_exercici_latex(self, node):
    self.body.append('\\begin{small}')

def depart_exercici_latex(self, node):
    self.body.append('\\end{small}\par')


def visit_problema(self, node): pass
def depart_problema(self, node): pass

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

class Numeros(Transform):
    default_priority = 710 
    def apply(self):
        pnum = 1
        for node in self.document.traverse(problema):
            title = nodes.strong()
            title += nodes.generated('', 'Problema %d\n' % pnum)
            node.children.insert(0, title)
            pnum += 1
        enum = 1
        for node in self.document.traverse(exercici):
            title = nodes.strong()
            title += nodes.generated('', 'Exercici %d  ' % enum)
            node.children.insert(0, title)
            enum += 1

# Setup

def setup(app):
    app.add_node(exercici,
                 html=(visit_exercici_html, depart_exercici_html),
                 latex=(visit_exercici_latex, depart_exercici_latex))
    app.add_node(problema,
                 html=(visit_problema, depart_problema),
                 latex=(visit_problema, depart_problema))

    app.add_directive('problema', ProblemaDirective)
    app.add_directive('exercici', ExerciciDirective)

    app.add_transform(Numeros)


