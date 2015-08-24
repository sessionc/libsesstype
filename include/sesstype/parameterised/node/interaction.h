#ifndef SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__
#define SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__

#include "sesstype/node/interaction.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/cond.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief InteractionNode (message-passing) statements (parameterised).
 */
class InteractionNode
    : public sesstype::InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> {
    MsgCond *cond_;

  public:
    InteractionNode()
        : InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>(),
          cond_(nullptr) { }

    InteractionNode(MsgSig *msg)
        : InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>(msg),
          cond_(nullptr) { }

    InteractionNode(const InteractionNode &node)
        : sesstype::InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>(node),
          cond_(node.cond_ ? node.cond_->clone() : nullptr) { }

    InteractionNode *clone() const override
    {
        return new InteractionNode(*this);
    }

    /// \returns message condition.
    MsgCond *cond() const
    {
        return cond_;
    }

    /// \brief Set message condition (only for send/receive).
    /// \param[in] cond for InteractionNode.
    void set_cond(MsgCond *cond)
    {
        if (cond_ != nullptr) {
            delete cond_;
        }
        cond_ = cond;
    }

    virtual void accept(util::NodeVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_param_interaction_node_init();

st_node *st_mk_param_interaction_node(st_msg *msg);

st_node *st_param_interaction_node_set_cond(st_node *const node, st_cond *cond);

st_cond *st_param_interaction_node_get_cond(st_node *const node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__INTERACTION__H__
