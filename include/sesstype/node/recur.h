#ifndef SESSTYPE__NODE__RECUR_H__
#define SESSTYPE__NODE__RECUR_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/node.h"

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

#ifdef __cplusplus
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

    void accept(util::NodeVisitor &v) override;

  private:
    std::string label_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_recur_node(char *label);

st_node *st_recur_node_set_label(st_node *node, char *label);
const char *st_recur_node_get_label(st_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__RECUR_H__
