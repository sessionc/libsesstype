#ifndef SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__
#define SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__

#include "sesstype/node/interaction.h"
#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/cond.h"
#include "sesstype/parameterised/msg.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief InteractionNode (message-passing) statements (parameterised).
 */
class InteractionNode : public sesstype::InteractionNode {
  public:
    /// \brief InteractionNode constructor with empty MsgSig.
    InteractionNode();

    /// \brief InteractionNode constructor for upgrading from sesstype::InteractionNode.
    InteractionNode(const sesstype::InteractionNode &node);

    /// \brief InteractionNode copy constructor.
    InteractionNode(const InteractionNode &node);

    /// \brief InteractionNode constructor.
    /// \param[in] msgsig for the interaction.
    InteractionNode(MsgSig *msgsig);

    /// \brief InteractionNode destructor.
    ~InteractionNode() override;

    InteractionNode *clone() const override;

    /// \returns message condition.
    MsgCond *cond() const;

    /// \brief Set message condition (only for send/receive).
    /// \param[in] cond for InteractionNode.
    void set_cond(MsgCond *cond);

    void accept(sesstype::util::NodeVisitor &v) override;

  private:
    MsgCond *msgcond_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_param_interaction_node_init();
st_node *st_mk_param_interaction_node(st_msg *msg);

st_node *st_param_interaction_node_set_cond(st_node *node, st_cond *cond);
st_cond *st_param_interaction_node_get_cond(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__
