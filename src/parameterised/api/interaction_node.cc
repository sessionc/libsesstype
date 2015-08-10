#include <sesstype/parameterised/msg.h>
#include <sesstype/parameterised/cond.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/interaction.h>

namespace sesstype {
namespace parameterised {

st_node *st_mk_param_interaction_node_init()
{
    return new InteractionNode();
}

st_node *st_mk_param_interaction_node(st_msg *msg)
{
    return new InteractionNode(msg);
}

st_node *st_param_interaction_node_set_cond(st_node *const node, st_cond *cond)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        inode->set_cond(cond);
    }
    return node;
}

st_cond *st_param_interaction_node_get_cond(st_node *const node)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        return inode->cond();
    }
    return nullptr;
}

} // namespace parameterised
} // namespace sesstype
