/**
 * \file sesstype/parameterised/protocol.h
 * \brief A protocol or a session of an interaction, also known in the
 * literature as global type (contains parameterised elements).
 */
#ifndef SESSTYPE__PARAMETERISED__PROTOCOL_H__
#define SESSTYPE__PARAMETERISED__PROTOCOL_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/protocol.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol class encapsulates a single protocol (parameterised flavour).
 */
class Protocol : public sesstype::Protocol {
  public:
    /// Protocol constructor with "default" as Protocol name.
    Protocol();

    /// Protocol constructor.
    /// \param[in] name Protocol name.
    Protocol(std::string name);

    /// Protocol destructor.
    ~Protocol();

    /// \param[in] name of the RoleGrp.
    /// \returns RoleGrp named name.
    /// \exception std::out_of_range_ if not found.
    RoleGrp *group(std::string name) const;

    /// \param[in] group to look for.
    /// \returns true if group is a RoleGrp in the Protocol.
    bool has_role_grp(RoleGrp *group) const;

    /// Add a RoleGrp as a participant of the Protocol.
    /// \param[in] group to add to this Protocol.
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

#endif//SESSTYPE__PARAMETERISED__PROTOCOL_H__
