#include <iterator>
#include <string>
#include <vector>

#include <sesstype/role.h>
#include <sesstype/parameterised/role.h>

namespace sesstype {
namespace parameterised {

Role::Role() : sesstype::Role(), param_()
{
}

Role::Role(std::string name) : sesstype::Role(name), param_()
{
}

Role::Role(const sesstype::Role &role) : sesstype::Role(role), param_()
{
}

Role::Role(const Role &role) : sesstype::Role(role), param_()
{
    for (auto &param : role.param_) {
        param_.push_back(param->clone());
    }
}

Role::~Role()
{
    for (auto *param : param_) {
        delete param;
    }
}

Role *Role::clone() const
{
    return new Role(*this);
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

bool Role::matches(sesstype::Role *other) const
{
    // TODO
    // go through each dimension, make sure other is in bound of this
    return false;
}

} // namespace parameterised
} // namespace sesstype
