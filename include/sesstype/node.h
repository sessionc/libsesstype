/**
 * \file sesstype/node.h
 * \brief Statements in a protocol or session.
 */
#ifndef SESSTYPE__NODE_H__
#define SESSTYPE__NODE_H__

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/util/clonable.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
class NodeVisitor;
} // namesapce util
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
class Node : public util::Clonable {
    unsigned int type_;

  public:
    /// \brief Node destructor.
    virtual ~Node() { }

    /// \returns type of Node.
    unsigned int type() const { return type_; }

    virtual void accept(util::NodeVisitor &v) { };

  protected:
    explicit Node(unsigned int type) : type_(type) { }
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

void st_node_free(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE_H__
