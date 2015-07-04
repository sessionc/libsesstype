#include <unordered_map>
#include <utility>

#include <sesstype/module.h>

namespace sesstype {

Module::Module() : name_("default"), imports_(), protocols_()
{
}

Module::Module(std::string name) : name_(name), imports_(), protocols_()
{
}

Module::~Module() {
  for (auto import_pair : imports_) {
    if (!import_pair.second.second /*alias?*/) {
      delete import_pair.second.first;
    }
  }
}

std::string Module::name() const
{
  return name_;
}

void Module::set_name(std::string name)
{
  name_ = name;
}

Import *Module::import(std::string name) const
{
  return imports_.at(name).first;
}

unsigned int Module::num_import() const
{
  return imports_.size();
}

bool Module::has_import(std::string name) const
{
  return (imports_.find(name) != imports_.end());
}

void Module::add_import(Import *import)
{
  imports_.insert({ import->name(), std::make_pair(import, false)});
  if (import->as() != "") {
    imports_.insert({ import->as(), std::make_pair(import, true/*alias*/)});
  }
}

Protocol *Module::protocol(std::string name) const
{
  return protocols_.at(name);
}

unsigned int Module::num_protocol() const
{
  return protocols_.size();
}

void Module::add_protocol(Protocol *protocol)
{
  protocols_.insert({ protocol->name(), protocol });
}

bool Module::has_protocol(std::string name) const
{
  return (protocols_.find(name) != protocols_.end());
}

} // namespace sesstype
