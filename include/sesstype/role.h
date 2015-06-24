/**
 * \file sesstype/role.h
 * \brief A participant of a protocol or session.
 */
#ifndef SESSTYPE__ROLE_H__
#define SESSTYPE__ROLE_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#endif

#include "sesstype/expr.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Role (participants) of a protocol or session.
 */
class Role {
  public:
    /// \brief Role constructor with "default" as name.
    Role();

    /// \brief Role constructor.
    Role(std::string name);

    /// \brief Role copy constructor.
    Role(const Role &role);

    /// \brief Role destructor.
    ~Role();

    /// \returns name of Role.
    std::string name();

    /// \param[in] name Sets role name to name.
    void set_name(std::string name);

    /// \returns Number of dimensions in the parameterised Role.
    unsigned int num_dimen();

    /// \param[in] param Adds parameter as a new dimension to the Role.
    void add_param(Expr *param);

    /// \param[in] idx Dimension index of parameterised Role.
    /// \returns expression at dimension idx.
    /// \exception std::out_of_range if dimension idx does not exist.
    Expr *operator[](std::size_t idx) const;

  private:
    std::string name_;
    std::vector<Expr *> param_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Role st_role;
#else
typedef struct Role st_role;
#endif

/// \brief Create a Role.
/// \param[in] name of Role.
/// \returns newly allocated Role.
st_role *st_role_init(const char *name);

/// \brief Create a copy of a Role.
/// \param[in] name of Role.
/// \returns pointer to newly allocated copy of Role.
st_role *st_role_copy(const st_role *const role);

/// \brief Get a name of the Role.
/// \param[in] role pointer.
/// \returns string name of Role.
const char *st_role_name(st_role *const role);

/// \brief Set the name of the Role.
/// \param[in,out] role pointer.
/// \param[in] name to use.
/// \returns the modified Role.
st_role *st_role_set_name(st_role *const role, const char *name);

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
st_role *st_role_add_param(st_role *const role, st_expr *param);

/// \brief Free a previously allocated Role.
/// \param[in] role pointer.
void st_role_free(st_role *role);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__ROLE_H__
