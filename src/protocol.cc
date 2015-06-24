#include <cstdlib>

#include <iostream>
#include <string>
#include <unordered_map>

#include <sesstype/constant.h>
#include <sesstype/protocol.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/role_grp.h>
#include <sesstype/utils.h>

namespace sesstype {

Protocol::Protocol()
    : name_("default"), me_(), root_(NULL), type_(ST_PROTOCOL_GLOBAL),
      roles_(), groups_()
{
}

Protocol::Protocol(std::string name)
    : name_(name), me_(), root_(NULL), type_(ST_PROTOCOL_GLOBAL),
      roles_(), groups_()
{
}

Protocol::~Protocol()
{
  for (auto role_pair : roles_) {
    delete role_pair.second;
  }
  if (root_ != NULL) {
    delete root_;
  }
}

std::string Protocol::name() const
{
  return name_;
}

void Protocol::set_root(Node *root)
{
  if (root_ != NULL) {
    delete root_;
  }
  root_ = root;
}

Node *Protocol::root() const
{
  return root_;
}

void Protocol::project(Role *role)
{
  utils::Projection projector(role);
  root_->accept(projector);
}

enum __st_prot_type Protocol::type() const
{
  return type_;
}

void Protocol::add_role(Role *role)
{
  roles_.insert({ role->name(), role });
}

bool Protocol::has_role(Role *role) const
{
  return (roles_.find(role->name()) != roles_.end());
}

void Protocol::add_group(RoleGrp *group)
{
  groups_.insert({ group->name(), group });
}

bool Protocol::has_role_grp(RoleGrp *group) const
{
  return (groups_.find(group->name()) != groups_.end());
}

RoleGrp *Protocol::group(std::string name) const
{
  return groups_.at(name);
}

} // namespace sesstype
