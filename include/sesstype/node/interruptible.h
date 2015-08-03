#ifndef SESSTYPE__NODE__INTERRUPTIBLE_H__
#define SESSTYPE__NODE__INTERRUPTIBLE_H__

#ifdef __cplusplus
#include <algorithm>
#include <string>
#include <unordered_map>
#endif

#include "sesstype/msg.h"
#include "sesstype/node.h"
#include "sesstype/role.h"
#include "sesstype/node/block.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Interruptible blocks.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class InterruptibleNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    std::string scope_;
    typename std::unordered_multimap<RoleType *, MessageType *> interrupts_;
    typename std::unordered_multimap<RoleType *, MessageType *> throws_;
    typename std::unordered_multimap<RoleType *, MessageType *> catches_;

  public:
    typedef typename std::unordered_multimap<RoleType *, MessageType *> InterruptType;

    /// \brief InterruptibleNode constructor with no scope name as default.
    InterruptibleNodeTmpl()
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_INTERRUPTIBLE),
          scope_(), interrupts_(), throws_(), catches_() { }

    /// \brief InterruptibleNode constructor.
    InterruptibleNodeTmpl(std::string scope)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_INTERRUPTIBLE),
          scope_(scope), interrupts_(), throws_(), catches_() { }


    /// \brief InterruptibleNode copy constructor.
    InterruptibleNodeTmpl(const InterruptibleNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node),
          scope_(node.scope_), interrupts_(), throws_(), catches_()
    {
        for (auto interrupt : node.interrupts_) {
            RoleType *role = interrupt.first->clone();
            MessageType *msg = interrupt.second->clone();
            add_interrupt(role, msg);
        }
        for (auto thr : node.throws_) {
            RoleType *role = thr.first->clone();
            MessageType *msg = thr.second->clone();
            add_throw(role, msg);
        }
        for (auto interrupt : node.catches_) {
            RoleType *role = interrupt.first->clone();
            MessageType *msg = interrupt.second->clone();
            add_catch(role, msg);
        }
    }

    /// \brief InterruptibleNode destructor.
    ~InterruptibleNodeTmpl() override
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

    /// \brief clone a InterruptibleNode.
    InterruptibleNodeTmpl *clone() const override
    {
        return new InterruptibleNodeTmpl(*this);
    }

    /// \param[in] scope_name to set for this interrupt.
    void set_scope(std::string scope)
    {
        scope_ = scope;
    }

    /// \returns scope name of interrupt.
    std::string scope() const
    {
        return scope_;
    }

    /// \brief add an interrupt specification for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_interrupt(RoleType *role, MessageType *msg)
    {
        interrupts_.insert({ role, msg });
    }

    /// \returns total number of interruptible rules.
    unsigned int num_interrupts() const
    {
        return interrupts_.size();
    }

    /// \returns number of interruptible rules for given role.
    unsigned int num_interrupts(RoleType *role) const
    {
        return std::count_if(interrupts_.begin(), interrupts_.end(),
                [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
    }

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MessageType *interrupt_msg(RoleType *role, unsigned int index) const
    {
        auto it = interrupts_.begin();
        for (unsigned int count=0; count <index; count++) {
            it = std::find_if(
                    ++it,
                    interrupts_.end(),
                    [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                        return (role->name() == pair.first->name());
                    });
        }
        return (*it).second;
    }

    typename InterruptType::const_iterator interrupt_begin() const
    {
        return interrupts_.begin();
    }

    typename InterruptType::const_iterator interrupt_end() const
    {
        return interrupts_.end();
    }

    /// \brief add an interrupt throw for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_throw(RoleType *role, MessageType *msg)
    {
        throws_.insert({ role, msg });
    }

    /// \returns total number of throw rules.
    unsigned int num_throws() const
    {
        return throws_.size();
    }

    /// \returns number of throw rules for given role.
    unsigned int num_throws(RoleType *role) const
    {
        return std::count_if(throws_.begin(), throws_.end(),
                [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });

    }

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MessageType *throw_msg(RoleType *role, unsigned int index) const
    {
        auto it = throws_.begin();
        for (unsigned int count=0; count <index; count++) {
            it = std::find_if(
                    ++it,
                    throws_.end(),
                    [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                        return (role->name() == pair.first->name());
                    });
        }
        return (*it).second;
    }

    typename InterruptType::const_iterator throw_begin() const
    {
        return throws_.begin();
    }

    typename InterruptType::const_iterator throw_end() const
    {
        return throws_.end();
    }

    /// \brief add an interrupt catch for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_catch(RoleType *role, MessageType *msg)
    {
        catches_.insert({ role, msg });
    }

    /// \returns total number of catch rules.
    unsigned int num_catches() const
    {
        return catches_.size();
    }

    /// \returns number of catch rules for given role.
    unsigned int num_catches(RoleType *role) const
    {
        return std::count_if(catches_.begin(), catches_.end(),
                [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                    return (role->name() == pair.first->name());
                });
    }

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MessageType *catch_msg(RoleType *role, unsigned int index) const
    {
        auto it = catches_.begin();
        for (unsigned int count=0; count <index; count++) {
            it = std::find_if(
                    ++it,
                    catches_.end(),
                    [role](std::pair<RoleType *, MessageType *> pair) -> bool {
                        return (role->name() == pair.first->name());
                    });
        }
        return (*it).second;
    }

    typename InterruptType::const_iterator catch_begin() const
    {
        return catches_.begin();
    }

    typename InterruptType::const_iterator catch_end() const
    {
        return catches_.end();
    }

    void accept(VisitorType &v) override;
};

using InterruptibleNode = InterruptibleNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_interruptible_node_init();
st_node *st_mk_interruptible_node_scoped(char *scope_name);

st_node *st_interruptible_node_add_interrupt(st_node *node, st_role *role, st_msg *msg);
unsigned int st_interruptible_node_num_interrupts(st_node *node, st_role *role);
st_msg *st_interruptible_node_interrupt(st_node *node, st_role *role, unsigned int index);

st_node *st_interruptible_node_add_throw(st_node *node, st_role *role, st_msg *msg);
unsigned int st_interruptible_node_num_throws(st_node *node, st_role *role);
st_msg *st_interruptible_node_throw(st_node *node, st_role *role, unsigned int index);

st_node *st_interruptible_node_add_catch(st_node *node, st_role *role, st_msg *msg);
unsigned int st_interruptible_node_num_catches(st_node *node, st_role *role);
st_msg *st_interruptible_node_catch(st_node *node, st_role *role, unsigned int index);

#ifdef __cplusplus
} // extern "C""
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__INTERRUPTIBLE_H__
