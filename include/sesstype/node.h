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

#define ST_NODE_ROOT     0
#define ST_NODE_SENDRECV 1
#define ST_NODE_CHOICE   2
#define ST_NODE_RECUR    3
#define ST_NODE_CONTINUE 4
#define ST_NODE_PARALLEL 5
#define ST_NODE_NESTED   6
#define ST_NODE_INTERRUPTIBLE 7

#ifdef __cplusplus
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
    unsigned int type() const;

    /// \brief <tt>accept</tt> method for util::NodeVisitor.
    virtual void accept(util::NodeVisitor &v) = 0;

  protected:
    explicit Node(unsigned int type);

  private:
    unsigned int type_;
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

    /// \brief clone a BlockNode.
    BlockNode *clone() const override;

    /// \brief Get child Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in BlockNode.
    /// \returns child Node at position <tt>idx</tt>.
    /// \exception std::out_of_range if <tt>idx</tt> is out of bounds.
    Node *child(unsigned int idx) const;

    /// \brief Get number of child statements (Node) in BlockNode.
    /// \returns number of child Node in current BlockNode.
    unsigned int num_children() const;

    /// \brief Add child Node to current Block.
    /// \param[in] child Node.
    void append_child(Node *child);

    /// \brief Start iterator for children.
    std::vector<Node *>::const_iterator child_begin() const;

    /// \brief End iterator for children.
    std::vector<Node *>::const_iterator child_end() const;

    void accept(util::NodeVisitor &v) override;

  protected:
    BlockNode(int type);
    std::vector<Node *> children_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Node st_node;
#else
typedef struct Node st_node;
#endif // __cplusplus

void st_node_append_child(st_node *parent, st_node *child);
unsigned int st_node_num_children(st_node *parent);
st_node *st_node_get_child(st_node *parent, unsigned int index);
void st_node_free(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE_H__
