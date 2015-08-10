#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/interaction.h>

namespace sesstype {

st_node *st_mk_interaction_node_init()
{
    return new InteractionNode();
}

st_node *st_mk_interaction_node(st_msg *msg)
{
    return new InteractionNode(msg);
}

st_node *st_interaction_node_set_msg(st_node *const node, st_msg *msg)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        inode->set_msg(msg);
    }
    return node;
}

st_msg *st_interaction_node_get_msg(st_node *const node)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        return inode->msg();
    }
    return nullptr;
}

st_node *st_interaction_node_set_from(st_node *const node, st_role *from)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        inode->set_sndr(from);
    }
    return node;
}
Role *st_interaction_node_get_from(st_node *const node)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        return inode->sndr();
    }
    return nullptr;
}

st_node *st_interaction_node_add_to(st_node *const node, st_role *to)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        inode->add_rcvr(to);
    }
    return node;
}

unsigned int st_interaction_node_num_tos(st_node *const node)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        return inode->num_rcvrs();
    }
    return 0;
}

st_role *st_interaction_node_get_to(st_node *const node, unsigned int index)
{
    if (auto inode = dynamic_cast<InteractionNode *>(node)) {
        return inode->rcvr(index);
    }
    return nullptr;
}

} // namespace sesstype
