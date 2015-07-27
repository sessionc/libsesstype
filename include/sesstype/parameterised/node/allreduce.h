#ifndef SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__
#define SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__

#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief All-to-all reduction statement.
 */
class AllReduceNode : public Node {
  public:
    /// \brief AllReduceNode constructor with no Msgsig as default (pure all2all).
    AllReduceNode();

    /// \brief AllReduceNode constructor.
    /// \param[in] msgsig for reduction.
    AllReduceNode(MsgSig *msgsig);

    /// \brief AllReduceNode copy constructor.
    AllReduceNode(const AllReduceNode &node);

    /// \brief AllReduceNode destructor.
    ~AllReduceNode() override;

    /// \brief clone a AllReduceNode.
    AllReduceNode *clone() const override;

    /// \returns message signature of AllReduceNode.
    MsgSig *msgsig() const;

    /// \brief Replace msgsig of AllReduceNode.
    /// \param[in] msgsig to replace with.
    void set_msgsig(MsgSig *msgsig);

    void accept(sesstype::util::NodeVisitor &v);

  private:
    MsgSig *msgsig_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_allreduce_node_init();
st_node *st_mk_allreduce_node(st_msg *msgsig);

st_node *st_allreduce_node_set_msgsig(st_node *node, st_msg *msgsig);
st_msg *st_allreduce_node_get_msgsig(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERIED__NODE__ALLREDUCE__H__
