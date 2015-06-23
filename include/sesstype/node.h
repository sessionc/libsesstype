/**
 * \file sesstype/node.h
 * \brief Statements in a protocol or session.
 */
#ifndef SESSTYPE__NODE_H__
#define SESSTYPE__NODE_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#endif

#include "sesstype/expr.h"
#include "sesstype/message.h"
#include "sesstype/role.h"

#ifdef __cplusplus
namespace sesstype {
#endif

enum __st_node_type {
  ST_NODE_ROOT,
  ST_NODE_SENDRECV,
  ST_NODE_CHOICE,
  ST_NODE_PARALLEL,
  ST_NODE_RECUR,
  ST_NODE_CONTINUE,
  ST_NODE_FOR,
  ST_NODE_ALLREDUCE,
  ST_NODE_ONEOF,
  ST_NODE_IF
};

#ifdef __cplusplus
typedef Role MsgCond;

namespace utils {
class NodeVisitor; // Forward declaration.
} // namespace utils

/**
 * \brief Session Type statements (st_node).
 *
 * Contains Node::accept method for visitors.
 */
class Node {
 public:
  /// \brief Node destructor.
  virtual ~Node();

  /// \returns type of Node.
  enum __st_node_type type() const;

  /// \brief <tt>accept</tt> method for utils::NodeVisitor.
  virtual void accept(utils::NodeVisitor &v) = 0;

 protected:
  Node(enum __st_node_type type);

 private:
  enum __st_node_type type_;
};

/**
 * \brief Block of statements (Node instances).
 */
class BlockNode : public Node {
  public:
    /// \brief BlockNode constructor.
    BlockNode();

    /// \brief BlockNode destructor.
    ~BlockNode() override;

    /// \brief Get child Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in BlockNode.
    /// \returns child Node at position <tt>idx</tt>.
    /// \exception std::out_of_range if <tt>idx</tt> is out of bounds.
    Node *child(unsigned int idx) const;

    /// \brief Get number of child statements (Node) in BlockNode.
    /// \returns number of child Node in current BlockNode.
    unsigned int num_child() const;

    /// \brief Add child Node to current Block.
    /// \param[in] child Node.
    void append_child(Node *child);

    /// \brief Start iterator for children.
    std::vector<Node *>::const_iterator child_begin() const;

    /// \brief End iterator for children.
    std::vector<Node *>::const_iterator child_end() const;

    void accept(utils::NodeVisitor &v) override;

  protected:
    BlockNode(enum __st_node_type type);
    std::vector<Node *> children_;
};

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

    /// \brief InteractionNode destructor.
    ~InteractionNode() override;

    /// \returns message condition.
    MsgCond *cond() const;

    /// \brief Set message condition (only for send/receive).
    /// \param[in] cond for InteractionNode.
    void set_cond(MsgCond *cond);

    /// \returns message signature of InteractionNode.
    MsgSig *msgsig() const;

    /// \brief Replace Msgsig of InteractionNode.
    /// \param[in] msgsig of InteractionNode to replace with.
    void set_msgsig(MsgSig *msgsig);

    /// \returns <tt>from</tt> Role of InteractionNode.
    Role *from() const;

    /// \param[in] from Role of InteractionNode.
    void set_from(Role *from);

    /// \brief Convenient function to return the first <tt>to</tt> Role.
    /// \returns the first <tt>to</tt> Role of InteractionNode.
    Role *to() const;

    /// \returns number of <tt>to</tt> Role.
    unsigned int num_to() const;

    /// \returns <tt>idx</tt>th <tt>to</tt> Role of InteractionNode.
    Role *to(unsigned int idx) const;

    /// \param[in] to Role to add to this InteractionNode.
    void add_to(Role *to);

    /// \brief Start iterator for to Role.
    std::vector<Role *>::const_iterator to_begin() const;

    /// \brief End iterator for to Role.
    std::vector<Role *>::const_iterator to_end() const;

    void accept(utils::NodeVisitor &v) override;

  private:
    MsgSig *msgsig_;
    Role *from_;
    std::vector<Role *> to_;
    MsgCond *msgcond_;
};

/**
 * \brief Recursion statements.
 */
class RecurNode : public BlockNode {
  public:
    /// \brief RecurNode constructor.
    /// \param[in] label of RecurNode.
    RecurNode(std::string label);

    /// \brief RecurNode destructor.
    ~RecurNode() override;

    /// \returns label of RecursionNode.
    std::string label() const;

    /// \brief Replace label of RecurNode.
    /// \param[in] label of RecurNode to replace with.
    void set_label(std::string label);

    void accept(utils::NodeVisitor &v) override;

  private:
    std::string label_;
};

/**
 * \brief Continue statements.
 */
class ContinueNode : public Node {
  public:
    /// \brief ContinueNode constructor.
    /// \param[in] label of Choice Node.
    ContinueNode(std::string label);

    /// \brief ContinueNode destructor.
    ~ContinueNode() override;

    /// \returns label of ContinueNode.
    std::string label() const;

    /// \brief Repalce label of ContinueNode.
    /// \param[in] label of ContinueNode to replace with.
    void set_label(std::string label);

    void accept(utils::NodeVisitor &v) override;

  private:
    std::string label_;
};

/**
 * \brief Choice blocks.
 */
class ChoiceNode : public BlockNode {
  public:
    /// \brief ChoiceNode constructor with empty Role as default.
    ChoiceNode();

    /// \brief ChoiceNode constructor.
    /// \param[in] at Role (choice maker).
    ChoiceNode(Role *at);

    /// \brief ChoiceNode destructor.
    ~ChoiceNode() override;

    /// \returns choice maker Role.
    Role *at() const;

    /// \param[in] at Role to set as choice maker.
    void set_atrole(Role *at);

    /// \param[in] choice Node to add as a branch.
    void add_choice(Node *choice);

    void accept(utils::NodeVisitor &v) override;

  private:
    Role *at_;
};

/**
 * \brief Counting for-loop statement.
 */
class ForNode : public BlockNode {
  public:
    /// \brief ForNode constructor.
    /// \param[in] bind_expr to add as index binding expression.
    ForNode(RngExpr *bind_expr);

    /// \brief ForNode destructor.
    ~ForNode() override;

    /// \returns binding expression of the for-loop.
    RngExpr *bind_expr() const;

    /// \brief Replace binding expression of for loop.
    /// \param[in] bind_expr to replace with.
    void set_bind_expr(RngExpr *bind_expr);

    void accept(utils::NodeVisitor &v) override;

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

    /// \brief AllReduceNode destructor.
    ~AllReduceNode() override;

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
    OneofNode(Role *selector_role, unsigned int dimen);

    /// \brief OneofNode destructor.
    ~OneofNode() override;

    /// \returns selector Role.
    Role *selector_role() const;

    /// \returns selector Role dimension.
    unsigned int selector_role_dimen() const;

    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    void set_selector_role(Role *selector_role, unsigned int dimen);

    /// \returns true if allow unordered access.
    bool unordered() const;

    /// \param[in] unordered flag.
    void set_unordered(bool unordered);

    void accept(utils::NodeVisitor &v) override;

  private:
    Role *selector_role_;
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

    /// \brief IfNode destructor.
    ~IfNode() override;

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

/**
 * \brief Namespace for utilities and non-datastructure classes.
 */
namespace utils {

/**
 * \brief Abstract class for building Node AST-based visitors.
 */
class NodeVisitor {
 public:
  //virtual void visit(Node *node) = 0;
  virtual void visit(InteractionNode *node) = 0;
  virtual void visit(BlockNode *node) = 0;
  virtual void visit(RecurNode *node) = 0;
  virtual void visit(ContinueNode *node) = 0;
  virtual void visit(ChoiceNode *node) = 0;
  virtual void visit(AllReduceNode *node) = 0;
  virtual void visit(ForNode *node) = 0;
  virtual void visit(OneofNode *node) = 0;
  virtual void visit(IfNode *node) = 0;
};

} // namespace utils
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef MsgPayload st_node_msgsig_payload;
typedef MsgSig st_node_msgsig;
typedef Node st_node;
#else
typedef struct MsgPayload st_node_msgsig_payload;
typedef struct MsgSig st_node_msgsig;
typedef struct Node st_node;
#endif // __cplusplus

typedef st_role msg_cond_t;

st_node *st_node_mk_interaction();
st_node *st_node_mk_recur(char *label);
st_node *st_node_mk_continue(char *label);
st_node *st_node_mk_choice(st_role *at_role);
st_node *st_node_mk_for(st_expr *bind_expr);
st_node *st_node_mk_allreduce();
st_node *st_node_mk_oneof();
st_node *st_node_mk_ifblk(msg_cond_t *cond);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE_H__
