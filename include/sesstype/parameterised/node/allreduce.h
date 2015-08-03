#ifndef SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__
#define SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__

#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief All-to-all reduction statement.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class AllReduceNodeTmpl : public BaseNode {
    MsgSig *msg_;

  public:
    /// \brief AllReduceNode constructor with no Msgsig as default (pure all2all).
    AllReduceNodeTmpl()
        : BaseNode(ST_NODE_ALLREDUCE), msg_(new MessageType("")) { }

    /// \brief AllReduceNode constructor.
    /// \param[in] msgsig for reduction.
    AllReduceNodeTmpl(MessageType *msg)
        : BaseNode(ST_NODE_ALLREDUCE), msg_(msg) { }

    /// \brief AllReduceNode copy constructor.
    AllReduceNodeTmpl(const AllReduceNodeTmpl &node)
        : Node(ST_NODE_ALLREDUCE), msg_(node.msg_) { }

    /// \brief clone a AllReduceNode.
    AllReduceNodeTmpl *clone() const override
    {
        return new AllReduceNodeTmpl(*this);
    }

    /// \brief Replace msgsig of AllReduceNode.
    /// \param[in] msgsig to replace with.
    void set_msg(MessageType *msg)
    {
        msg_ = msg;
    }

    /// \returns message signature of AllReduceNode.
    MessageType *msg() const
    {
        return msg_;
    }

    virtual void accept(VisitorType &v) override;
};

using AllReduceNode = AllReduceNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_allreduce_node_init();

st_node *st_mk_allreduce_node(st_msg *msg);

st_node *st_allreduce_node_set_msgsig(st_node *node, st_msg *msg);

st_msg *st_allreduce_node_get_msgsig(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__
