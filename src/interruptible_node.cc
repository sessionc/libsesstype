#include <algorithm>
#include <string>
#include <iterator>
#include <unordered_map>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/interruptible.h>

namespace sesstype {

InterruptibleNode::InterruptibleNode()
    : BlockNode(ST_NODE_INTERRUPTIBLE),
      scope_name_(),
      interrupts_(),
      throws_(),
      catches_()
{
}

InterruptibleNode::InterruptibleNode(std::string scope_name)
    : BlockNode(ST_NODE_INTERRUPTIBLE),
      scope_name_(scope_name),
      interrupts_(),
      throws_(),
      catches_()
{
}

InterruptibleNode::InterruptibleNode(const InterruptibleNode &node)
    : BlockNode(node),
      scope_name_(node.scope_name_),
      interrupts_(),
      throws_(),
      catches_()
{
    for (auto interrupt : node.interrupts_) {
        Role *role = interrupt.first->clone();
        MsgSig *msg = interrupt.second->clone();
        add_interrupt(role, msg);
    }

    for (auto interrupt : node.throws_) {
        Role *role = interrupt.first->clone();
        MsgSig *msg = interrupt.second->clone();
        add_throw(role, msg);
    }

    for (auto interrupt : node.catches_) {
        Role *role = interrupt.first->clone();
        MsgSig *msg = interrupt.second->clone();
        add_catch(role, msg);
    }
}

InterruptibleNode::~InterruptibleNode()
{
    for (auto interrupt : interrupts_) {
        delete interrupt.first;
        delete interrupt.second;
    }
    interrupts_.clear();

    for (auto thr : throws_) {
        delete thr.first;
        delete thr.second;
    }
    throws_.clear();

    for (auto cat : catches_) {
        delete cat.first;
        delete cat.second;
    }
    catches_.clear();
}

InterruptibleNode *InterruptibleNode::clone() const
{
    return new InterruptibleNode(*this);
}

void InterruptibleNode::set_scope(std::string scope_name)
{
    scope_name_ = scope_name;
}

std::string InterruptibleNode::scope() const
{
    return scope_name_;
}

void InterruptibleNode::add_interrupt(Role *role, MsgSig *msg)
{
    interrupts_.insert({ role, msg });
}

unsigned int InterruptibleNode::num_interrupts() const
{
    return interrupts_.size();
}

unsigned int InterruptibleNode::num_interrupts(Role *role) const
{
   return std::count_if(interrupts_.begin(), interrupts_.end(),
            [role](std::pair<Role *, MsgSig *> pair) -> bool {
                return (role->name() == pair.first->name());
            });
}

MsgSig *InterruptibleNode::interrupt_msg(Role *role, unsigned int index) const
{
    auto it = interrupts_.begin();
    for (unsigned int count=0; count <index; count++) {
        it = std::find_if(
                ++it,
                interrupts_.end(),
                [role](std::pair<Role *, MsgSig *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
    }
    return (*it).second;
}

void InterruptibleNode::add_throw(Role *role, MsgSig *msg)
{
    throws_.insert({ role, msg });
}

unsigned int InterruptibleNode::num_throws() const
{
    return throws_.size();
}

unsigned int InterruptibleNode::num_throws(Role *role) const
{
   return std::count_if(throws_.begin(), throws_.end(),
            [role](std::pair<Role *, MsgSig *> pair) -> bool {
                return (role->name() == pair.first->name());
            });
}

MsgSig *InterruptibleNode::throw_msg(Role *role, unsigned int index) const
{
    auto it = throws_.begin();
    for (unsigned int count=0; count <index; count++) {
        it = std::find_if(
                ++it,
                throws_.end(),
                [role](std::pair<Role *, MsgSig *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
    }
    return (*it).second;
}

void InterruptibleNode::add_catch(Role *role, MsgSig *msg)
{
    catches_.insert({ role, msg });
}


unsigned int InterruptibleNode::num_catches() const
{
    return catches_.size();
}


unsigned int InterruptibleNode::num_catches(Role *role) const
{
    return std::count_if(catches_.begin(), catches_.end(),
                [role](std::pair<Role *, MsgSig *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
}

MsgSig *InterruptibleNode::catch_msg(Role *role, unsigned int index) const
{
    auto it = catches_.begin();
    for (unsigned int count=0; count <index; count++) {
        it = std::find_if(
                ++it,
                catches_.end(),
                [role](std::pair<Role *, MsgSig *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
    }
    return (*it).second;
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::interrupt_begin() const
{
    return interrupts_.begin();
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::interrupt_end() const
{
    return interrupts_.end();
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::throw_begin() const
{
    return throws_.begin();
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::throw_end() const
{
    return throws_.end();
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::catch_begin() const
{
    return catches_.begin();
}

std::unordered_multimap<Role *, MsgSig *>::const_iterator InterruptibleNode::catch_end() const
{
    return catches_.end();
}

} // namespace sesstype
