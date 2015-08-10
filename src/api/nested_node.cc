#include <sesstype/msg.h>
#include <sesstype/role.h>
#include <sesstype/node.h>
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

st_node *st_nested_node_add_arg(st_node *const node, st_msg *arg)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        nested->add_arg(arg);
    }
    return node;
}

unsigned int st_nested_node_num_args(st_node *const node)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        return nested->num_args();
    }
    return 0;
}

st_msg *st_nested_node_get_arg(st_node *const node, unsigned int index)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        return nested->arg(index);
    }
    return nullptr;
}

st_node *st_nested_node_add_rolearg(st_node *const node, st_role *rolearg)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        nested->add_arg(rolearg);
    }
    return node;
}

unsigned int st_nested_node_num_roleargs(st_node *const node)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        return nested->num_roleargs();
    }
    return 0;
}

st_role *st_nested_node_get_rolearg(st_node *const node, unsigned int index)
{
    if (auto nested = dynamic_cast<NestedNode *>(node)) {
        return nested->rolearg(index);
    }
    return nullptr;
}

} // namespace sesstype
