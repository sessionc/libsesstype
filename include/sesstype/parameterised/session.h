/**
 * \file sesstype/parameterised/session.h
 * \brief A session or a session of an interaction, also known in the
 * literature as global type (contains parameterised elements).
 */
#ifndef SESSTYPE__PARAMETERISED__SESSION_H__
#define SESSTYPE__PARAMETERISED__SESSION_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/session.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Session class encapsulates a single session (parameterised flavour).
 */
class Session : public sesstype::Session {
  public:
    /// Session constructor with "default" as Session name.
    Session();

    /// Session constructor.
    /// \param[in] name Session name.
    Session(std::string name);

    /// Session destructor.
    ~Session();

    /// \param[in] name of the RoleGrp.
    /// \returns RoleGrp named name.
    /// \exception std::out_of_range_ if not found.
    RoleGrp *group(std::string name) const;

    /// \param[in] group to look for.
    /// \returns true if group is a RoleGrp in the Session.
    bool has_role_grp(RoleGrp *group) const;

    /// Add a RoleGrp as a participant of the Session.
    /// \param[in] group to add to this Session.
    void add_group(RoleGrp *group);

  private:
    std::unordered_map<std::string, RoleGrp *> groups_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void st_tree_add_role_grp(st_tree *tree, const st_role_grp *grp);
bool st_tree_has_role_grp(st_tree *const tree, const char *grp_name);
st_role_grp *st_tree_get_role_grp(st_tree *const tree, const char *grp_name);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__SESSION_H__
