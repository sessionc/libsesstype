#include <unordered_map>
#include <utility>

#include <sesstype/module.h>
#include <sesstype/parameterised/module.h>

namespace sesstype {
namespace parameterised {

Module::Module() : sesstype::Module(), consts_()
{
}

Module::Module(std::string name) : sesstype::Module(), consts_()
{
}

Module::~Module() {
  for (auto constant_pair : consts_) {
    delete constant_pair.second;
  }
}

Constant *Module::constant(std::string name) const
{
  return consts_.at(name);
}

unsigned int Module::num_constant() const
{
  return consts_.size();
}

bool Module::has_constant(std::string name) const
{
  return (consts_.find(name) != consts_.end());
}

void Module::add_constant(Constant *c)
{
  consts_.insert({ c->name(), c });
}

} // namespace parameterised
} // namespace sesstype
