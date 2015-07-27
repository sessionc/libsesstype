/**
 * \file sesstype/parameterised/role.h
 * \brief A (parameterised) participant of a protocol or session.
 */
#ifndef SESSTYPE__PARAMETERISED__ROLE_H__
#define SESSTYPE__PARAMETERISED__ROLE_H__

#include "sesstype/role.h"

#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/util/role_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {

namespace util {
class RoleVisitor;
} // namespace util
#endif

#ifdef __cplusplus
/**
 * \brief Parameterised Role (participant) of a protocol or session.
 */
class Role : public sesstype::Role {
  public:
    /// \brief Role constructor with "default" as name.
    Role();

    /// \brief Role constructor.
    Role(std::string name);

    /// \brief Role constructor for upgrading from sesstype::Role..
    Role(const sesstype::Role &role);

    /// \brief Role copy constructor.
    Role(const Role &role);

    /// \brief Role destructor.
    ~Role() override;

    /// \brief clone a Role
    Role *clone() const override;

    /// \returns Number of dimensions in the parameterised Role.
    unsigned int num_dimen();

    /// \param[in] param Adds parameter as a new dimension to the Role.
    void add_param(Expr *param);

    /// \param[in] idx Dimension index of parameterised Role.
    /// \returns expression at dimension idx.
    /// \exception std::out_of_range if dimension idx does not exist.
    Expr *operator[](std::size_t idx) const;

    /// \brief Check if this Role contains another Role.
    /// \returns true if this Role contains another Role.
    bool matches(sesstype::Role *other) const override;

    using sesstype::Role::accept;

    void accept(sesstype::parameterised::util::RoleVisitor &v);

  private:
    std::vector<Expr *> param_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Role st_role;
#endif

/// \brief Get the total dimension of a Role.
/// \param[in] role pointer.
/// \returns the dimension of the Role.
unsigned int st_role_num_dimen(st_role *const role);

/// \brief Get the idx'th dimension parameter of a Role.
/// \param[in] role pointer.
/// \returns the idx'th dimension parameter of the Role.
st_expr *st_role_get_param(st_role *const role, unsigned int idx);

/// \brief Add a new parameter to the Role as a new dimension.
/// \param[in] role pointer.
/// \param[in] param Expr.
/// \returns the modified Role.
st_role *st_role_add_param(st_role *role, st_expr *param);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__ROLE_H__
