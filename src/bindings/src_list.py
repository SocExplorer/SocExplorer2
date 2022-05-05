#!/bin/env python3
# taken from https://github.com/radareorg/cutter/blob/master/src/bindings/src_list.py


import os
import sys
import xml.etree.ElementTree as ET


script_path = os.path.dirname(os.path.realpath(__file__))

def typenames_and_namespaces(root, namespace=''):
    result = []
    prefix = namespace + '_' if namespace != '' else ''
    for child in root:
        if child.tag == 'namespace-type':
            result.append(prefix + child.attrib['name'])
            result += typenames_and_namespaces(child,child.attrib['name'])
        elif child.tag == 'object-type':
            result.append(prefix + child.attrib['name'])
    return result

def get_cpp_files_gen(args, include_package=True):
    tree = ET.parse('bindings.xml')
    root = tree.getroot()
    package = root.attrib['package']
    types = typenames_and_namespaces(root)

    cpp_files_gen = [f"{package.lower()}_module_wrapper.cpp"]
    cpp_files_gen.extend([f"{typename.lower()}_wrapper.cpp" for typename in types])

    if include_package:
        cpp_files_gen = [os.path.join(package, f) for f in cpp_files_gen]

    if len(args) > 0:
        cpp_files_gen = [os.path.join(args[0], f) for f in cpp_files_gen]

    return cpp_files_gen

def cmd_meson(args):
    sys.stdout.write(";".join(get_cpp_files_gen(args, include_package=False)))


cmds = {"meson": cmd_meson}

if len(sys.argv) < 2 or sys.argv[1] not in cmds:
    print(f"""usage: {sys.argv[0]} [{"/".join(cmds.keys())}] [base path]""")
    exit(1)
cmds[sys.argv[1]](sys.argv[2:])
