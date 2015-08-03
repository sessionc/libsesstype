#ifndef SESSTYPE__PARAMETERIED__NODE__FOR__H__
#define SESSTYPE__PARAMETERIED__NODE__FOR__H__

#ifdef __cplusplus
#include <iostream>
#endif

#include "sesstype/node/block.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/expr/rng.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Counting for-loop statement.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class ForNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    RngExpr *bindexpr_;
    std::string except_idx_;

  public:
    /// \brief ForNode constructor.
    /// \param[in] bind_expr to add as index binding expression.
    ForNodeTmpl(RngExpr *bindexpr)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_FOR),
          bindexpr_(bindexpr) { }

    /// \brief ForNode copy constructor.
    ForNodeTmpl(const ForNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_FOR),
          bindexpr_(node.bindexpr_) { }

    /// \brief ForNode destructor.
    ~ForNodeTmpl() override
    {
        delete bindexpr_;
    }

    /// \brief clone a ForNode.
    ForNodeTmpl *clone() const override
    {
        return new ForNodeTmpl(*this);
    }

    /// \brief Replace binding expression of for loop.
    /// \param[in] bind_expr to replace with.
    void set_bindexpr(RngExpr *bindexpr)
    {
        delete bindexpr_;
        bindexpr_ = bindexpr;
    }

    /// \returns binding expression of the for-loop.
    RngExpr *bindexpr() const
    {
        if (bindexpr_ == NULL) {
            std::cerr << "Warning: bind_expr is NULL.\n";
        }
        return bindexpr_;
    }

    virtual void accept(VisitorType &v) override;
};

using ForNode = ForNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
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
