#include <string>

#include <sesstype/import.h>

namespace sesstype {

Import::Import(std::string name) : name_(name), from_(), as_()
{
}

Import::Import(std::string name, std::string from, std::string as)
    : name_(name), from_(from), as_(as)
{
}

std::string Import::name() const
{
  return name_;
}

std::string Import::from() const
{
  return from_;
}

std::string Import::as() const
{
  return as_;
}

} // namespace sesstype
