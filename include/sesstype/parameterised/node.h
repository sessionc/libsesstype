/**
 * \file sesstype/parameterised/node.h
 * \brief Statements in a protocol or session (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__NODE_H__
#define SESSTYPE__PARAMETERISED__NODE_H__

#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
class NodeVisitor;
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#define ST_NODE_FOR       101
#define ST_NODE_ALLREDUCE 102
#define ST_NODE_ONEOF     103
#define ST_NODE_IF        104

#ifdef __cplusplus
class Node : public sesstype::Node {
  public:
    /// This subsumes accept in base class (but RoleVisitor is not a subclass)
    virtual void accept(util::NodeVisitor &v) = 0;

    friend std::ostream &operator<<(std::ostream &os, Node &node);

  protected:
    explicit Node(unsigned int type) : sesstype::Node(type) { }

  private:
    virtual void accept(sesstype::util::NodeVisitor &v) override { };
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Node st_param_node;
#else
typedef struct Node st_param_node;
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE_H__
