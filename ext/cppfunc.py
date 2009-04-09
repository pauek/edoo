# -*- coding: utf-8 -*-
# He tenido que copiar el código de sphinx a muerte...
# La clase CDesc no es muy reutilizable

import re, string
from docutils import nodes
from docutils.parsers.rst import directives
from sphinx import addnodes
from sphinx.directives.desc import DescDirective
from sphinx.util.compat import directive_dwim

cpp_sig_re = re.compile(
    r'''^([^(]*?)          # return type
        ([\w:<>]+)  \s*    # thing name (colon + angles for C++)
        (?: \((.*)\) )?    # optionally arguments
        (\s+const)? $      # const specifier
    ''', re.VERBOSE)

wsplit_re = re.compile(r'(\W+)')
c_funcptr_name_re = re.compile(r'^\(\s*\*\s*(.*?)\s*\)$')

class CppFuncDirective(DescDirective):
    """
    Based on Sphinx CDesc: An ugly hack for C++ functions
    """

    # These C types aren't described anywhere, so don't try to create
    # a cross-reference to them
    stopwords = set(('const', 'void', 'char', 'int', 'long', 'FILE', 'struct'))

    def _parse_type(self, node, ctype):
        # add cross-ref nodes for all words
        for part in filter(None, wsplit_re.split(ctype)):
            tnode = nodes.Text(part, part)
            if part[0] in string.ascii_letters+'_' and \
                   part not in self.stopwords:
                pnode = addnodes.pending_xref(
                    '', reftype='ctype', reftarget=part,
                    modname=None, classname=None)
                pnode += tnode
                node += pnode
            else:
                node += tnode

    def parse_signature(self, sig, signode):
        """Transform a C (or C++) signature into RST nodes."""
        # first try the function pointer signature regex, it's more specific
        m = cpp_sig_re.match(sig)
        if m is None:
            raise ValueError('no match')
        rettype, name, arglist, const = m.groups()

        signode += addnodes.desc_type('', '')
        self._parse_type(signode[-1], rettype)
        try:
            classname, funcname = name.split('::', 1)
            classname += '::'
            signode += addnodes.desc_addname(classname, classname)
            signode += addnodes.desc_name(funcname, funcname)
            # name (the full name) is still both parts
        except ValueError:
            signode += addnodes.desc_name(name, name)
        # clean up parentheses from canonical name
        m = c_funcptr_name_re.match(name)
        if m:
            name = m.group(1)
        if not arglist:
            signode += addnodes.desc_parameterlist()
	    if const:
	      	signode += addnodes.desc_addname(const, const)
            return name

        paramlist = addnodes.desc_parameterlist()
        arglist = arglist.replace('`', '').replace('\\ ', '') # remove markup
        # this messes up function pointer types, but not too badly ;)
        args = arglist.split(',')
        for arg in args:
            arg = arg.strip()
            param = addnodes.desc_parameter('', '', noemph=True)
            try:
                ctype, argname = arg.rsplit(' ', 1)
            except ValueError:
                # no argument name given, only the type
                self._parse_type(param, arg)
            else:
                self._parse_type(param, ctype)
                param += nodes.emphasis(' '+argname, ' '+argname)
            paramlist += param
        signode += paramlist
        if const:
            signode += addnodes.desc_addname(const, const)
        return name

    def add_target_and_index(self, name, sig, signode):
        # note target
        if name not in self.state.document.ids:
            signode['names'].append(name)
            signode['ids'].append(name)
            signode['first'] = (not self.names)
            self.state.document.note_explicit_target(signode)
            self.env.note_descref(name, self.desctype, self.lineno)

        try: 
            classname, funcname = name.split('::', 1)
            indextext = "%s; %s" % (classname, funcname)
            self.indexnode['entries'].append(('pair', indextext, name, name))
        except:
            indextext = name
            self.indexnode['entries'].append(('single', indextext, name, name))
