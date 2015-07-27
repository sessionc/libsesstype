#ifndef SESSTYPE__PARAMETERISED__NODE__ONEOF_H__
#define SESSTYPE__PARAMETERISED__NODE__ONEOF_H__

#ifdef __cplusplus
#include <string>
#endif

#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/role.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
namespace util {
class NodeVisitor;
} // namespace util
#endif

#ifdef __cplusplus
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Existential construct.
 */
class OneofNode : public BlockNode {
  public:
    /// \brief OneofNode constructor.
    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    OneofNode(parameterised::Role *selector, unsigned int dimen);

    /// \brief OneofNode copy constructor.
    OneofNode(const OneofNode &node);

    /// \brief OneofNode destructor.
    ~OneofNode() override;

    /// \brief clone a OneofNode.
    OneofNode *clone() const override;

    /// \param[in] var to be used as existential variable name.
    void set_var(std::string var);

    /// \returns existential variable.
    std::string var() const;

    /// \param[in] repeat boolean to indicate whether or not this is "repeat".
    void set_repeat(bool repeat);

    /// \return true if this is a repeat-oneof.
    bool is_repeat() const;

    /// \param[in] range without variable.
    void set_range(RngExpr *range);

    /// \return range of selection.
    RngExpr *range() const;

    /// \param[in] selector_role Role to use as selector.
    /// \param[in] dimen of the Role parameters to use as selector index domain.
    void set_selector(Role *selector, unsigned int dimen);

    /// \returns selector Role.
    Role *selector_role() const;

    /// \returns selector Role dimension.
    unsigned int selector_dimen() const;

    /// \param[in] unordered flag.
    void set_unordered(bool unordered);

    /// \returns true if allow unordered access.
    bool is_unordered() const;

    void accept(sesstype::util::NodeVisitor &v) override;

  private:
    parameterised::Role *selector_role_;
    unsigned int selector_dimen_;
    RngExpr *range_;
    std::string var_;
    bool unordered_;
    bool repeat_;
};
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
