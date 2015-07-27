#ifndef SESSTYPE__PARAMETERIED__NODE__FOR__H__
#define SESSTYPE__PARAMETERIED__NODE__FOR__H__

#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Counting for-loop statement.
 */
class ForNode : public BlockNode {
  public:
    /// \brief ForNode constructor.
    /// \param[in] bind_expr to add as index binding expression.
    ForNode(RngExpr *bindexpr);

    /// \brief ForNode copy constructor.
    ForNode(const ForNode &node);

    /// \brief ForNode destructor.
    ~ForNode() override;

    /// \brief clone a ForNode.
    ForNode *clone() const override;

    /// \returns binding expression of the for-loop.
    RngExpr *bindexpr() const;

    /// \brief Replace binding expression of for loop.
    /// \param[in] bind_expr to replace with.
    void set_bindexpr(RngExpr *bindexpr);

    void accept(sesstype::util::NodeVisitor &v) override;

  private:
    RngExpr *bindexpr_;
    std::string except_idx_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_for_node(st_rng_expr *bindexpr);

st_rng_expr *st_for_node_get_bindexpr(st_node *node);
st_node *st_for_node_set_bindexpr(st_node *node, st_rng_expr *bindexpr);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERIED__NODE__FOR__H__
