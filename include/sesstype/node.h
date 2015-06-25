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

#include "sesstype/msg.h"
#include "sesstype/role.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#define ST_NODE_ROOT     0
#define ST_NODE_SENDRECV 1
#define ST_NODE_CHOICE   2
#define ST_NODE_PARALLEL 3
#define ST_NODE_RECUR    4
#define ST_NODE_CONTINUE 5

#ifdef __cplusplus
typedef Role MsgCond;

namespace utils {
class NodeVisitor;
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

    /// \brief clone a Node (abstract).
    virtual Node *clone() const = 0;

    /// \returns type of Node.
    int type() const;

    /// \brief <tt>accept</tt> method for utils::NodeVisitor.
    virtual void accept(utils::NodeVisitor &v) = 0;

  protected:
    Node(int type);

  private:
    int type_;
};

/**
 * \brief Block of statements (Node instances).
 */
class BlockNode : public Node {
  public:
    /// \brief BlockNode constructor.
    BlockNode();

    /// \brief BlockNode copy constructor.
    BlockNode(const BlockNode &node);

    /// \brief BlockNode destructor.
    ~BlockNode() override;

    /// \brief clone a BlocNode.
    BlockNode *clone() const override;

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
    BlockNode(int type);
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

    /// \brief InteractionNode copy constructor.
    InteractionNode(const InteractionNode &node);

    /// \brief InteractionNode constructor.
    /// \param[in] msgsig for the interaction.
    InteractionNode(MsgSig *msgsig);

    /// \brief InteractionNode destructor.
    ~InteractionNode() override;

    /// \brief clone a InteractionNode.
    InteractionNode *clone() const override;

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
};

/**
 * \brief Recursion statements.
 */
class RecurNode : public BlockNode {
  public:
    /// \brief RecurNode constructor.
    /// \param[in] label of RecurNode.
    RecurNode(std::string label);

    /// \brief RecurNode copy constructor.
    RecurNode(const RecurNode &node);

    /// \brief RecurNode destructor.
    ~RecurNode() override;

    /// \brief clone a RecurNode.
    RecurNode *clone() const override;

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

    /// \brief ContinueNode copy constructor.
    ContinueNode(const ContinueNode &node);

    /// \brief ContinueNode destructor.
    ~ContinueNode() override;

    /// \brief clone a ContinueNode.
    ContinueNode *clone() const override;

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

    /// \brief ChoiceNode copy constructor.
    ChoiceNode(const ChoiceNode &node);

    /// \brief ChoiceNode destructor.
    ~ChoiceNode() override;

    /// \brief clone a ChoiceNode.
    ChoiceNode *clone() const override;

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

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE_H__
