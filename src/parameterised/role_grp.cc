#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <sesstype/role.h>
#include <sesstype/parameterised/role_grp.h>

namespace sesstype {
namespace parameterised {

// RoleGrp -------------------------------------------------------------------

RoleGrp::RoleGrp() : Role("default_grp"), members_()
{
}

RoleGrp::RoleGrp(std::string name) : Role(name), members_()
{
}

RoleGrp::RoleGrp(const RoleGrp &role) : Role(role), members_(role.members_)
{
    // We don't explicitly copy members because this is a shallow copy (of ptr)
}

RoleGrp::~RoleGrp()
{
  // Note: member Role pointers are deallocated by protocol.
}

RoleGrp *RoleGrp::clone() const
{
    return new RoleGrp(*this);
}

Role *RoleGrp::member(std::string name) const
{
  return members_.at(name);
}

unsigned int RoleGrp::num_member() const
{
  return members_.size();
}

void RoleGrp::add_member(Role *role)
{
  members_.insert({ role->name(), role });
}

bool RoleGrp::matches(sesstype::Role *role) const
{
    // TODO
    return false;
}

std::unordered_map<std::string, Role *>::const_iterator RoleGrp::member_begin() const
{
  return members_.begin();
}

std::unordered_map<std::string, Role *>::const_iterator RoleGrp::member_end() const
{
  return members_.end();
}

} // namespace parameterised
} // namespace sesstype
