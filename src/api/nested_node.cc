#include <iostream>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/nested.h>

namespace sesstype {

st_node *st_mk_nested_node(char *protocol_name)
{
    return new NestedNode(protocol_name);
}

st_node *st_mk_nested_node_scoped(char *protocol_name, char *scope_name)
{
    return new NestedNode(protocol_name, scope_name);
}

st_node *st_nested_node_add_arg(st_node *node, st_msg *arg)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        nested->add_arg(arg);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
    }
    return node;
}

unsigned int st_nested_node_num_args(st_node *node)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        return nested->num_args();
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
        return 0;
    }
}

st_msg *st_nested_node_get_arg(st_node *node, unsigned int index)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        return nested->arg(index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
        return nullptr;
    }
}

st_node *st_nested_node_add_rolearg(st_node *node, st_role *rolearg)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        nested->add_arg(rolearg);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
    }
    return node;
}

unsigned int st_nested_node_num_roleargs(st_node *node)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        return nested->num_roleargs();
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
        return 0;
    }
}

st_role *st_nested_node_get_rolearg(st_node *node, unsigned int index)
{
    if (NestedNode *nested = dynamic_cast<NestedNode *>(node)) {
        return nested->rolearg(index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not a Nested.\n";
        return nullptr;
    }
}

} // namespace sesstype
