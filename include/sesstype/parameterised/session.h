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

#include "sesstype/parameterised/node.h"
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
template <class NodeType, class RoleType, class RoleGrpType>
class SessionTmpl : public sesstype::SessionTmpl<NodeType, RoleType> {
    std::unordered_map<std::string, RoleGrpType *> groups_;

  public:
    using RoleGrpContainer = std::unordered_map<std::string, RoleGrpType *>;
    /// Session constructor with "default" as Session name.
    SessionTmpl() : sesstype::SessionTmpl<NodeType, RoleType>(), groups_() { }

    /// Session constructor.
    /// \param[in] name Session name.
    SessionTmpl(std::string name)
        : sesstype::SessionTmpl<NodeType, RoleType>(name), groups_() { }

    /// Session destructor.
    virtual ~SessionTmpl()
    {
        for (auto grp_pair : groups_) {
            delete grp_pair.second;
        }
    }

    /// \param[in] name of the RoleGrp.
    /// \returns RoleGrp named name.
    /// \exception std::out_of_range_ if not found.
    RoleGrpType *group(std::string name) const
    {
        return groups_.at(name);
    }

    /// \param[in] group to look for.
    /// \returns true if group is a RoleGrp in the Session.
    bool has_role_grp(std::string name) const
    {
        return (groups_.find(name) != groups_.end());
    }

    /// Add a RoleGrp as a participant of the Session.
    /// \param[in] group to add to this Session.
    void add_group(RoleGrpType *group)
    {
        groups_.insert(std::pair<std::string, RoleGrpType *>(group->name(), group));
    }

    unsigned int num_groups() const
    {
        return groups_.size();
    }

    typename RoleGrpContainer::const_iterator rolegrp_begin() const
    {
        return groups_.begin();
    }

    typename RoleGrpContainer::const_iterator rolegrp_end() const
    {
        return groups_.end();
    }
};

using Session = SessionTmpl<Node, Role, RoleGrp>;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Session st_param_tree;
#else
typedef struct Session st_param_tree;
#endif

/// \param[in] name of the session.
/// \returns pointer to session object allocated dynamically.
st_param_tree *st_param_tree_mk_init(const char *name);

/// \param[in,out] tree pointer to session object.
/// \param[in] role of the local session.
/// \returns pointer to modified session object.
st_param_tree *st_param_tree_add_role(st_param_tree *const tree, st_role *role);

/// \param[in,out] tree pointer to session object.
/// \parma[in] root to use.
/// \returns pointer to modified session object.
st_param_tree *st_param_tree_set_root(st_param_tree *const tree, st_node *root);

/// \param[in,out] tree pointer to session object.
/// \returns pointer to root (body of session).
st_param_node *st_param_tree_get_root(st_param_tree *const tree);

st_param_tree *st_param_tree_add_role_grp(st_param_tree *tree, st_role_grp *grp);

bool st_param_tree_has_role_grp(st_param_tree *const tree, const char *grp_name);

st_role_grp *st_param_tree_get_role_grp(st_param_tree *const tree, const char *grp_name);

/// \param[in,out] session object to destroy.
void st_param_tree_free(st_param_tree *tree);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__SESSION_H__
