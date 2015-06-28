#include <string>

#include <sesstype/role.h>

namespace sesstype {

Role::Role() : name_("default")
{
}

Role::Role(std::string name) : name_(name)
{
}

Role::Role(const Role &role) : name_(role.name_)
{
}

Role::~Role()
{
}

Role *Role::clone() const
{
    return new Role(*this);
}

std::string Role::name() const
{
    return name_;
}

void Role::set_name(std::string name)
{
    name_ = name;
}

bool Role::matches(sesstype::Role *other) const
{
    return (other->name() == name_);
}

} // namespace sesstype
