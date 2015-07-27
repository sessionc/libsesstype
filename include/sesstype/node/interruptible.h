#ifndef SESSTYPE__NODE__INTERRUPTIBLE_H__
#define SESSTYPE__NODE__INTERRUPTIBLE_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {

class NodeVisitor;

} // namespace util
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Interruptible blocks.
 */
class InterruptibleNode : public virtual BlockNode {
  public:
    /// \brief InterruptibleNode constructor with no scope name as default.
    InterruptibleNode();

    /// \brief InterruptibleNode constructor.
    InterruptibleNode(std::string scope_name);

    /// \brief InterruptibleNode copy constructor.
    InterruptibleNode(const InterruptibleNode &node);

    /// \brief InterruptibleNode destructor.
    ~InterruptibleNode() override;

    /// \brief clone a InterruptibleNode.
    InterruptibleNode *clone() const override;

    /// \param[in] scope_name to set for this interrupt.
    void set_scope(std::string scope_name);

    /// \returns scope name of interrupt.
    std::string scope() const;

    /// \brief add an interrupt specification for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_interrupt(Role *role, MsgSig *msg);

    /// \returns total number of interruptible rules.
    unsigned int num_interrupts() const;

    /// \returns number of interruptible rules for given role.
    unsigned int num_interrupts(Role *role) const;

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MsgSig *interrupt_msg(Role *role, unsigned int index) const;

    /// \brief add an interrupt throw for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_throw(Role *role, MsgSig *msg);

    /// \returns total number of throw rules.
    unsigned int num_throws() const;

    /// \returns number of throw rules for given role.
    unsigned int num_throws(Role *role) const;

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MsgSig *throw_msg(Role *role, unsigned int index) const;

    /// \brief add an interrupt catch for a Role.
    /// \param[in] role that can send interrupt.
    /// \param[in] msg as an interrupt message.
    void add_catch(Role *role, MsgSig *msg);

    /// \returns total number of catch rules.
    unsigned int num_catches() const;

    /// \returns number of catch rules for given role.
    unsigned int num_catches(Role *role) const;

    /// \param[in] role that can send interrupt.
    /// \param[in] index of the interrupt messages.
    /// \returns interrupt message.
    MsgSig *catch_msg(Role *role, unsigned int index) const;

    void accept(util::NodeVisitor &v) override;

    std::unordered_multimap<Role *, MsgSig *>::const_iterator interrupt_begin() const;
    std::unordered_multimap<Role *, MsgSig *>::const_iterator interrupt_end() const;
    std::unordered_multimap<Role *, MsgSig *>::const_iterator throw_begin() const;
    std::unordered_multimap<Role *, MsgSig *>::const_iterator throw_end() const;
    std::unordered_multimap<Role *, MsgSig *>::const_iterator catch_begin() const;
    std::unordered_multimap<Role *, MsgSig *>::const_iterator catch_end() const;

  private:
    std::string scope_name_;
    std::unordered_multimap<Role *, MsgSig *> interrupts_;
    std::unordered_multimap<Role *, MsgSig *> throws_;
    std::unordered_multimap<Role *, MsgSig *> catches_;
};
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
