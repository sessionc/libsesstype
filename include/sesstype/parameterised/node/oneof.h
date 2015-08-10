#ifndef SESSTYPE__PARAMETERISED__NODE__ONEOF_H__
#define SESSTYPE__PARAMETERISED__NODE__ONEOF_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/node/block.h"
#include "sesstype/util/visitor_tmpl.h"

#include "sesstype/parameterised/msg.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/expr/rng.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Existential construct.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class OneofNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
    RoleType *selector_role_;
    unsigned int selector_dimen_;
    RngExpr *range_;
    std::string var_;
    bool unordered_;
    bool repeat_;

  public:
    /// \brief OneofNode constructor.
    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    OneofNodeTmpl(RoleType *selector, unsigned int dimen)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_ONEOF),
          selector_role_(selector),
          selector_dimen_(dimen),
          range_(),
          var_(),
          unordered_(false),
          repeat_(false) { }

    /// \brief OneofNode copy constructor.
    OneofNodeTmpl(const OneofNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node),
          selector_role_(node.selector_role_),
          selector_dimen_(node.selector_dimen_),
          range_(),
          var_(),
          unordered_(false),
          repeat_(false) { }

    /// \brief clone a OneofNode.
    OneofNodeTmpl *clone() const override
    {
        return new OneofNodeTmpl(*this);
    }

    /// \param[in] var to be used as existential variable name.
    void set_var(std::string var)
    {
        var_ = var;
    }

    /// \returns existential variable.
    std::string var() const
    {
        return var_;
    }

    /// \param[in] repeat boolean to indicate whether or not this is "repeat".
    void set_repeat(bool repeat)
    {
        repeat_ = repeat;
    }

    /// \return true if this is a repeat-oneof.
    bool is_repeat() const
    {
        return repeat_;
    }

    /// \param[in] range without variable.
    void set_range(RngExpr *range)
    {
        range_ = range;
    }

    /// \return range of selection.
    RngExpr *range() const
    {
        return range_;
    }

    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    void set_selector(RoleType *selector, unsigned int dimen)
    {
        selector_role_ = selector;
        selector_dimen_ = dimen;
    }

    /// \returns selector Role.
    RoleType *selector_role() const
    {
        return selector_role_;
    }

    /// \returns selector Role dimension.
    unsigned int selector_dimen() const
    {
        return selector_dimen_;
    }

    /// \param[in] unordered flag.
    void set_unordered(bool unordered)
    {
        unordered_ = unordered;
    }

    /// \returns true if allow unordered access.
    bool is_unordered() const
    {
        return unordered_;
    }

    virtual void accept(VisitorType &v) override;
};

using OneofNode = OneofNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_oneof_node(st_role *selector_role, unsigned int dimen);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif


#endif//SESSTYPE__PARAMETERISED__NODE__ONEOF_H__
