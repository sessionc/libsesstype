#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#include <sesstype/role.h>

namespace sesstype {

Role::Role() : name_("default"), param_()
{
}

Role::Role(std::string name) : name_(name), param_()
{
}

Role::Role(const Role &role) : name_(role.name_), param_()
{
    for (Expr *e : role.param_) {
        param_.push_back(e->clone());
    }
}

Role::~Role()
{
    for (Expr *e : param_) {
        delete e;
    }
}

void Role::set_name(std::string name)
{
    if (name == "") {
        name_ = name;
    } else {
        throw std::invalid_argument("Role already has a name");
    }
}

std::string Role::name()
{
    return name_;
}

unsigned int Role::num_dimen()
{
    return param_.size();
}

void Role::add_param(Expr *param)
{
    param_.push_back(param);
}

Expr *Role::operator[](std::size_t idx) const
{
    return param_.at(idx);
}

} // namespace sesstype
