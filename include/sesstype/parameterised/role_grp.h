/**
 * \file sesstype/parameterised/role_grp.h
 * \brief A group of participants of a protocol or session.
 */
#ifndef SESSTYPE__PARAMETERISED__ROLE_GRP_H__
#define SESSTYPE__PARAMETERISED__ROLE_GRP_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/role.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {

namespace util {
class RoleVisitor;
} // namespace util
#endif

#ifdef __cplusplus
/**
 * \brief Role Group (group of participants) of a protocol or session.
 */
class RoleGrp : public sesstype::Role {
  public:
    /// \brief RoleGrp constructor with "default_grp" as name.
    RoleGrp();

    /// \brief RoleGrp constructor.
    RoleGrp(std::string name);

    /// \brief RoleGrp copy constructor.
    RoleGrp(const RoleGrp &role);

    /// \brief RoleGrp destructor.
    ///
    /// Roles in the RoleGrp are not freed (they are owned by the Protocol).
    ~RoleGrp() override;

    /// \brief clone a RoleGrp.
    RoleGrp *clone() const override;

    /// \param[in] name of the member Role.
    /// \returns member Role.
    /// \exception std::out_of_range if Role is not in the RoleGrp.
    sesstype::Role *member(std::string name) const;

    /// \returns number of members.
    unsigned int num_member() const;

    /// \param[in] role to add as member.
    void add_member(sesstype::Role *role);

    /// \brief Check if this Role contains another Role.
    /// \returns true if this Role contains another Role.
    bool matches(sesstype::Role *other) const override;

    /// \brief Start iterator for member.
    std::unordered_map<std::string, sesstype::Role *>::const_iterator member_begin() const;

    /// \brief End iterator for member.
    std::unordered_map<std::string, sesstype::Role *>::const_iterator member_end() const;

    using sesstype::Role::accept;

    void accept(sesstype::parameterised::util::RoleVisitor &v);

  private:
    std::unordered_map<std::string, sesstype::Role *> members_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef RoleGrp st_role_grp;
#else
typedef struct RoleGrp st_role_grp;
#endif

st_role_grp *st_role_grp_init(const char *name);

const char *st_role_grp_name(const st_role_grp * const role_grp);
st_role_grp *st_role_grp_set_name(st_role_grp * const role_grp, const char *name);

void st_role_grp_add_member(st_role *role);
unsigned int st_role_grp_num_member(const st_role_grp * const role_grp);
void st_role_grp_free(st_role_grp *role_grp);

#ifdef __cplusplus
}; // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__ROLE_GRP_H__
