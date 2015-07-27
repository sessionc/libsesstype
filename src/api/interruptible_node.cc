#include <iostream>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/interruptible.h>

namespace sesstype {

st_node *st_mk_interruptible_node_init()
{
    return new InterruptibleNode();
}

st_node *st_mk_interruptible_node_scoped(char *scope_name)
{
    return new InterruptibleNode(scope_name);
}

st_node *st_interruptible_node_add_interrupt(st_node *node, st_role *role, st_msg *msg)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        interruptible->add_interrupt(role, msg);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
    }
    return node;
}

unsigned int st_interruptible_node_num_interrupts(st_node *node, st_role *role)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->num_interrupts(role);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return 0;
    }
}
st_msg *st_interruptible_node_interrupt(st_node *node, st_role *role, unsigned int index)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->interrupt_msg(role, index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return nullptr;
    }
}

st_node *st_interruptible_node_add_throw(st_node *node, st_role *role, st_msg *msg)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        interruptible->add_throw(role, msg);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
    }
    return node;
}

unsigned int st_interruptible_node_num_throws(st_node *node, st_role *role)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->num_throws(role);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return 0;
    }
}

st_msg *st_interruptible_node_throw(st_node *node, st_role *role, unsigned int index)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->throw_msg(role, index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return nullptr;
    }
}

st_node *st_interruptible_node_add_catch(st_node *node, st_role *role, st_msg *msg)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        interruptible->add_catch(role, msg);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
    }
    return node;
}

unsigned int st_interruptible_node_num_catches(st_node *node, st_role *role)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->num_catches(role);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return 0;
    }
}
st_msg *st_interruptible_node_catch(st_node *node, st_role *role, unsigned int index)
{
    if (InterruptibleNode *interruptible = dynamic_cast<InterruptibleNode *>(node)) {
        return interruptible->catch_msg(role, index);
    } else {
        std::cerr << __FILE__ << ":" << __LINE__ << ": "
                  << __FUNCTION__ << ": node is not Interruptible.\n";
        return nullptr;
    }
}

} // namespace sesstype
