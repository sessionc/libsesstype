#include <cstdlib>

#include <string>
#include <unordered_map>

#include <sesstype/session.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/util.h>

namespace sesstype {

Session::Session()
    : name_("default"), type_(ST_TYPE_GLOBAL), me_(), root_(NULL), roles_()
{
}

Session::Session(std::string name)
    : name_(name), type_(ST_TYPE_GLOBAL), me_(), root_(NULL), roles_()
{
}

Session::~Session()
{
    for (auto role_pair : roles_) {
        delete role_pair.second;
    }
    if (root_ != NULL) {
        delete root_;
    }
}

std::string Session::name() const
{
    return name_;
}

void Session::set_root(Node *root)
{
    if (root_ != NULL) {
        delete root_;
    }
    root_ = root;
}

Node *Session::root() const
{
    return root_;
}

Role *Session::endpoint() const
{
    return me_;
}

void Session::set_endpoint(Role *endpoint)
{
    me_ = endpoint;
}

void Session::project(Role *role)
{
    //util::Projection projection_visitor(role);
    //root_->accept(projection_visitor);
}

int Session::type() const
{
  return type_;
}

void Session::add_role(Role *role)
{
  roles_.insert({ role->name(), role });
}

bool Session::has_role(Role *role) const
{
  return (roles_.find(role->name()) != roles_.end());
}

} // namespace sesstype
