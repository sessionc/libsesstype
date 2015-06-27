/**
 * \file sesstype/parameterised/node.h
 * \brief Statements in a protocol or session (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__NODE_H__
#define SESSTYPE__PARAMETERISED__NODE_H__

#include "sesstype/node.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/role.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#define  ST_NODE_FOR       101
#define  ST_NODE_ALLREDUCE 102
#define  ST_NODE_ONEOF     103
#define  ST_NODE_IF        104

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

    void accept(sesstype::utils::NodeVisitor &v) override;

  private:
    MsgCond *msgcond_;
};
/**
 * \brief Counting for-loop statement.
 */
class ForNode : public BlockNode {
  public:
    /// \brief ForNode constructor.
    /// \param[in] bind_expr to add as index binding expression.
    ForNode(RngExpr *bind_expr);

    /// \brief ForNode copy constructor.
    ForNode(const ForNode &node);

    /// \brief ForNode destructor.
    ~ForNode() override;

    /// \brief clone a ForNode.
    ForNode *clone() const override;

    /// \returns binding expression of the for-loop.
    RngExpr *bind_expr() const;

    /// \brief Replace binding expression of for loop.
    /// \param[in] bind_expr to replace with.
    void set_bind_expr(RngExpr *bind_expr);

    void accept(sesstype::utils::NodeVisitor &v) override;

  private:
    RngExpr *bind_expr_;
    std::string except_idx_;
};

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

    void accept(utils::NodeVisitor &v) override;

  private:
    MsgSig *msgsig_;
};

/**
 * \brief Existential construct.
 */
class OneofNode : public BlockNode {
  public:
    /// \brief OneofNode constructor.
    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    OneofNode(parameterised::Role *selector_role, unsigned int dimen);

    /// \brief OneofNode copy constructor.
    OneofNode(const OneofNode &node);

    /// \brief OneofNode destructor.
    ~OneofNode() override;

    /// \brief clone a OneofNode.
    OneofNode *clone() const override;

    /// \returns selector Role.
    Role *selector_role() const;

    /// \returns selector Role dimension.
    unsigned int selector_role_dimen() const;

    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    void set_selector_role(parameterised::Role *selector_role, unsigned int dimen);

    /// \returns true if allow unordered access.
    bool unordered() const;

    /// \param[in] unordered flag.
    void set_unordered(bool unordered);

    void accept(utils::NodeVisitor &v) override;

  private:
    parameterised::Role *selector_role_;
    unsigned int selector_role_dimen_;
    bool unordered_;
};

/**
 * \brief If-block.
 */
class IfNode : public BlockNode {
  public:
    /// \brief IfNode constructor.
    /// \param[in] cond for the if-block.
    IfNode(MsgCond *cond);

    /// \brief IfNode copy constructor.
    IfNode(const IfNode &node);

    /// \brief IfNode destructor.
    ~IfNode() override;

    /// \brief clone a IfNode.
    IfNode *clone() const override;

    /// \brief Get body Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in IfNode.
    /// \returns body Node at position <tt>idx</tt>
    /// \exception std::out_of_range if <tt>idx</tt> is out of bounds.
    Node *body(unsigned int idx) const;

    /// \brief Add body Node to current if-block
    /// \param[in] body Node.
    void append_body(Node *body);

    /// \returns if-block condition.
    MsgCond *cond() const;

    /// \brief Set if-block condition.
    /// \param[in] cond for the if-block.
    void set_cond(MsgCond *cond);

    void accept(utils::NodeVisitor &v) override;

  private:
    MsgCond *cond_;
};

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_node_mk_for(st_expr *bind_expr);
st_node *st_node_mk_allreduce();
st_node *st_node_mk_oneof();
st_node *st_node_mk_ifblk(msg_cond_t *cond);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE_H__
