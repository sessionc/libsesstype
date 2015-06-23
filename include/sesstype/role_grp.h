/**
 * \file sesstype/role_grp.h
 * \brief A group of participants of a protocol or session.
 */
#ifndef SESSTYPE__ROLE_GRP_H__
#define SESSTYPE__ROLE_GRP_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/role.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Role Group (group of participants) of a protocol or session.
 */
class RoleGrp {
  public:
    /// \brief RoleGrp constructor with "default_grp" as name.
    RoleGrp();
    /// \brief RoleGrp constructor.
    RoleGrp(std::string name);
    /// \brief RoleGrp destructor.
    ///
    /// Roles in the RoleGrp are not freed (they are owned by the Protocol).
    ~RoleGrp();

    /// \returns RoleGrp name.
    std::string name() const;

    /// \param[in] name to set as new RoleGrp name.
    void set_name(std::string name);

    /// \param[in] name of the member Role.
    /// \returns member Role.
    /// \exception std::out_of_range if Role is not in the RoleGrp.
    Role *member(std::string name) const;

    /// \returns number of members.
    unsigned int num_member() const;

    /// \param[in] role to add as member.
    void add_member(Role *role);

    /// \brief Start iterator for member.
    std::unordered_map<std::string, Role *>::const_iterator member_begin() const;

    /// \brief End iterator for member.
    std::unordered_map<std::string, Role *>::const_iterator member_end() const;

  private:
    std::string name_;
    std::unordered_map<std::string, Role *> members_;
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
} // namespace sesstype
#endif

#endif
