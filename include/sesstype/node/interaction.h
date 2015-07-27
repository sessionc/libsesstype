#ifndef SESSTYPE__NODE__INTERACTION_H__
#define SESSTYPE__NODE__INTERACTION_H__

#ifdef __cplusplus
#include <vector>
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
 * \brief Interaction (message-passing) statements.
 *
 * InteractionNode also encapsulates send-only and receive-only statements.
 */
class InteractionNode : public Node {
  public:
    /// \brief InteractionNode constructor with empty MsgSig.
    InteractionNode();

    /// \brief InteractionNode constructor.
    /// \param[in] msgsig for the interaction.
    InteractionNode(MsgSig *msgsig);

    /// \brief InteractionNode copy constructor.
    InteractionNode(const InteractionNode &node);

    /// \brief InteractionNode destructor.
    ~InteractionNode() override;

    /// \brief clone a InteractionNode.
    InteractionNode *clone() const override;

    /// \brief Replace Msgsig of InteractionNode.
    /// \param[in] msgsig of InteractionNode to replace with.
    void set_msgsig(MsgSig *msgsig);

    /// \returns message signature of InteractionNode.
    MsgSig *msgsig() const;

    /// \param[in] from Role of InteractionNode.
    void set_from(Role *from);

    /// \returns <tt>from</tt> Role of InteractionNode.
    Role *from() const;

    /// \brief Remove from Role.
    void remove_from();

    /// \param[in] to Role to add to this InteractionNode.
    void add_to(Role *to);

    /// \returns number of <tt>to</tt> Role.
    unsigned int num_tos() const;

    /// \brief Convenient function to return the first <tt>to</tt> Role.
    /// \returns the first <tt>to</tt> Role of InteractionNode.
    Role *to() const;

    /// \returns <tt>index</tt>th <tt>to</tt> Role of InteractionNode.
    Role *to(unsigned int index) const;

    /// \brief Remove to Role (all of them);
    void clear_to();

    /// \brief Start iterator for to Role.
    std::vector<Role *>::const_iterator to_begin() const;

    /// \brief End iterator for to Role.
    std::vector<Role *>::const_iterator to_end() const;

    void accept(util::NodeVisitor &v) override;

  private:
    MsgSig *msgsig_;
    Role *from_;
    std::vector<Role *> to_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_interaction_node_init();
st_node *st_mk_interaction_node(st_msg *msg);

st_node *st_interaction_node_set_msgsig(st_node *node, st_msg *msgsig);
st_msg *st_interaction_node_get_msgsig(st_node *node);

st_node *st_interaction_node_set_from(st_node *node, Role *from_role);
Role *st_interaction_node_get_from(st_node *node);

st_node *st_interaction_node_add_to(st_node *node, Role *to_role);
unsigned int st_interaction_node_num_tos(st_node *node);

Role **st_interaction_node_get_tos(st_node *node);
Role *st_interaction_node_get_to(st_node *node, unsigned int index);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__INTERACTION_H__
