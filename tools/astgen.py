#!/usr/bin/python3

SPACES_PER_TAB = 4
TAB            = ' ' * SPACES_PER_TAB

def main():
    hpp_file = create_ast('Expr',
        [
            'Binary  : Expr left, lex::Token op, Expr right',
            'Literal : int val'
        ]
    )
    print(hpp_file)

def create_ast(base_name, types_list):
    '''Gives AST specification return AST hpp string.'''
    lines = list()
    p_types_list = parse_types_list(base_name, types_list)
    lines = append_forward_declarations(p_types_list, lines)
    lines = append_generic_type(base_name, p_types_list, lines)
    lines = append_visitor_interface(base_name, p_types_list, lines)
    lines = append_node_definitions(base_name, p_types_list, lines)
    lines = wrap_namespace(base_name, lines)
    lines = prepend_includes(lines)
    lines = wrap_file_defines(base_name, lines)
    return '\n'.join(lines)

def parse_types_list(base_name, types_list):
    '''Parses types list into a preformatted structure.
    
    Performatted structure:
        [
            (node_name1, [(field_type1, field_name1), ...])
            ...
        ]
    '''
    parsed_list = list()
    for type_def in types_list:
        type_def = type_def.split(':')
        node_name = type_def[0].strip()

        field_defs = ":".join(type_def[1:])        
        fields = list()
        for field_def in field_defs.split(','):
            field_type, field_name = field_def.strip().split(' ')
            # Normalize base_name to boost::variant name
            if field_type == base_name: 
                field_type = '{}_t'.format(base_name.lower())
            fields.append((field_type, field_name))

        parsed_list.append((node_name, fields))        

    return parsed_list

def wrap_file_defines(base_name, body):
    '''Wraps C++ header collision macro to the around the body.'''
    file_macro = "__{}_H__".format(base_name.upper())
    header = [
        f'#ifndef {file_macro}',
        f'#define {file_macro}',
        ''
    ]
    footer = [
        '',
        f'#endif /* {file_macro} */'
    ]

    return header + body + footer

def prepend_includes(body):
    '''Prepends required include statements to the top of the file.'''
    includes = [
        '#include <boost/variant.hpp>',
        '#include "lex.hpp"',
        '',
    ]
    return includes + body

def wrap_namespace(base_name, body):
    '''Wraps base_name namespace around the body.'''
    return [f'namespace {base_name.lower()} {{'] \
        + body \
        + ['}']

def append_forward_declarations(p_types_list, body):
    '''Appends forward declarations of the node_names.'''
    forward_decls = [
        TAB + f'class {node_name};'
        for (node_name, _) in p_types_list
    ]
    return body + forward_decls

def append_generic_type(base_name, p_types_list, body):
    '''Appends boost::variant recursive types for base_name.'''
    base_name_t = '{}_t'.format(base_name.lower())
    generic_type = \
          [
            '',
            TAB + f'using {base_name_t} = boost::variant<'
          ] \
        + [
            2 * TAB + 'boost::recursive_wrapper<{}>{}'.format(
                node_name,
                ',' if i != len(p_types_list) - 1 else ''
            )
            for (i, (node_name, _)) in enumerate(p_types_list)
          ] \
        + [TAB + '>;']
    return body + generic_type

def append_visitor_interface(base_name, p_types_list, body):
    '''Appends boost::static_visitor<R> visitor interface.'''
    visitor_interface = \
          [
            '',
            TAB + 'template <class R>',
            TAB + f'class {base_name}VisitorInterface : public boost::static_visitor<R> {{',
            TAB + 'public:'
          ] \
        + [
            2 * TAB + f'virtual R operator()({node_name}& expr) = 0;'
            for (node_name, _) in p_types_list
        ] \
        + [TAB + '};']
    return body + visitor_interface

def append_node_definitions(base_name, p_types_list, body):
    '''Appends node definitions.'''
    visitor_name = '{}VisitorInterface'.format(base_name)
    node_defs = list()
    for (node_name, field_defs) in p_types_list:
        node_def = \
              [
                TAB + 'class ' + node_name + '{',
                TAB + 'public:',
              ] \
            + [
                2 * TAB + f'{" ".join(field)};'
                for field in field_defs
              ] \
            + [
                '',
                2 * TAB + '{}({})'.format(
                    node_name,
                    ', '.join(f'{field_type} {field_name}_' for (field_type, field_name) in field_defs)
                )
              ] \
            + [
                3 * TAB + '{0} {1}({1}_)'.format(
                    ':' if i == 0 else ',',
                    field_name
                )
                for (i, (_, field_name)) in enumerate(field_defs)
              ] \
            + [
                2 * TAB + '{}',
                '',
                2 * TAB + 'template <class R>',
                2 * TAB + f'R apply_visitor({visitor_name}<R>& visitor) {{',
                3 * TAB + 'return visitor(*this);',
                2 * TAB + '}',
                TAB + '};'
            ]
        node_defs = node_defs + [''] + node_def
    return body + node_defs

    
if __name__ == '__main__':
    main()
