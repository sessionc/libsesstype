#include <cstdlib>

#include <iostream>
#include <string>
#include <unordered_map>

#include <sesstype/protocol.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/utils.h>

namespace sesstype {

Protocol::Protocol()
    : name_("default"), type_(ST_PROTOCOL_GLOBAL), me_(), root_(NULL), roles_()
{
}

Protocol::Protocol(std::string name)
    : name_(name), type_(ST_PROTOCOL_GLOBAL), me_(), root_(NULL), roles_()
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

int Protocol::type() const
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

} // namespace sesstype
