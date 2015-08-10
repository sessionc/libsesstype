#include <sesstype/msg.h>
#include <sesstype/role.h>
#include <sesstype/node.h>
#include <sesstype/node/interruptible.h>

namespace sesstype {

st_node *st_mk_interruptible_node_init()
{
    return new InterruptibleNode();
}

st_node *st_mk_interruptible_node_scoped(char *scope)
{
    return new InterruptibleNode(scope);
}

st_node *st_interruptible_node_add_interrupt(st_node *const node, st_role *role, st_msg *msg)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        inode->add_interrupt(role, msg);
    }
    return node;
}

unsigned int st_interruptible_node_num_interrupts(st_node *const node, st_role *role)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->num_interrupts(role);
    }
    return 0;
}

st_msg *st_interruptible_node_interrupt(st_node *const node, st_role *role, unsigned int index)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->interrupt_msg(role, index);
    }
    return nullptr;
}

st_node *st_interruptible_node_add_throw(st_node *const node, st_role *role, st_msg *msg)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        inode->add_throw(role, msg);
    }
    return node;
}

unsigned int st_interruptible_node_num_throws(st_node *const node, st_role *role)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->num_throws(role);
    }
    return 0;
}

st_msg *st_interruptible_node_throw(st_node *const node, st_role *role, unsigned int index)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->throw_msg(role, index);
    }
    return nullptr;
}

st_node *st_interruptible_node_add_catch(st_node *const node, st_role *role, st_msg *msg)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        inode->add_catch(role, msg);
    }
    return node;
}

unsigned int st_interruptible_node_num_catches(st_node *const node, st_role *role)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->num_catches(role);
    }
    return 0;
}

st_msg *st_interruptible_node_catch(st_node *const node, st_role *role, unsigned int index)
{
    if (auto inode = dynamic_cast<InterruptibleNode *>(node)) {
        return inode->catch_msg(role, index);
    }
    return nullptr;
}

} // namespace sesstype
