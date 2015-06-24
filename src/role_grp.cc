#include <iterator>
#include <string>
#include <unordered_map>

#include <sesstype/role.h>
#include <sesstype/role_grp.h>

namespace sesstype {

// RoleGrp -------------------------------------------------------------------

RoleGrp::RoleGrp() : name_("default_grp"), members_()
{
}

RoleGrp::RoleGrp(std::string name) : name_(name), members_()
{
}

RoleGrp::~RoleGrp()
{
  // Note: member Role pointers are deallocated by protocol.
}

std::string RoleGrp::name() const
{
  return name_;
}

void RoleGrp::set_name(std::string name)
{
  name_ = name;
}

void RoleGrp::add_member(Role *role)
{
  members_.insert({ role->name(), role });
}

unsigned int RoleGrp::num_member() const
{
  return members_.size();
}

Role *RoleGrp::member(std::string name) const
{
  return members_.at(name);
}

std::unordered_map<std::string, Role *>::const_iterator RoleGrp::member_begin() const
{
  return members_.begin();
}

std::unordered_map<std::string, Role *>::const_iterator RoleGrp::member_end() const
{
  return members_.end();
}

} // namespace sesstype
