/**
 * \file sesstype/parameterised/role_grp.h
 * \brief A group of participants of a protocol or session.
 */
#ifndef SESSTYPE__PARAMETERISED__ROLE_GRP_H__
#define SESSTYPE__PARAMETERISED__ROLE_GRP_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#endif

#include "sesstype/parameterised/role.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Role Group (group of participants) of a protocol or session.
 */
class RoleGrp : public Role {
    std::vector<sesstype::parameterised::Role *> members_;

  public:
    typedef std::vector<sesstype::parameterised::Role *> RoleContainer;

    /// \brief RoleGrp constructor with "default_grp" as name.
    RoleGrp() : Role("default_grp"), members_() { }

    /// \brief RoleGrp constructor.
    RoleGrp(std::string name) : Role(name), members_() { }

    /// \brief RoleGrp copy constructor.
    RoleGrp(const RoleGrp &role) : Role(role), members_(role.members_)
    {
        // We don't explicitly copy members
        // --> because this is a shallow copy (of ptr)
    }

    /// \brief RoleGrp destructor.
    ///
    /// Roles in the RoleGrp are not freed (they are owned by the Protocol).
    ~RoleGrp() override { }

    /// \brief clone a RoleGrp.
    RoleGrp *clone() const override
    {
        return new RoleGrp(*this);
    }

    /// \param[in] index of the member Role.
    /// \returns member Role.
    /// \exception std::out_of_range if Role is not in the RoleGrp.
    sesstype::Role *member(unsigned int index) const
    {
        return members_.at(index);
    }

    /// \returns number of members.
    unsigned int num_members() const
    {
        return members_.size();
    }

    /// \param[in] role to add as member.
    void add_member(Role *role)
    {
        members_.push_back(role);
    }

    /// \brief Check if this Role contains another Role.
    /// \returns true if this Role contains another Role.
    bool matches(sesstype::Role *other) const override
    {
        if (auto other_param = dynamic_cast<Role *>(other)) {
            for (auto it=member_begin(); it!=member_end(); it++) {
                if (!(*it)->matches(other_param)) return false;
            }
            return true;
        }
        return false;
    }

    /// \brief Start iterator for member.
    RoleContainer::const_iterator member_begin() const
    {
        return members_.begin();
    }

    /// \brief End iterator for member.
    RoleContainer::const_iterator member_end() const
    {
        return members_.end();
    }

    virtual void accept(util::RoleVisitor &v) override;
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

void st_role_grp_add_member(st_param_role *role);
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
