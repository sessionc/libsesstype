#include <unordered_map>
#include <utility>

#include <sesstype/module.h>
#include <sesstype/session.h>
#include <sesstype/import.h>

namespace sesstype {

Module::Module() : name_("default"), imports_(), sessions_()
{
}

Module::Module(std::string name) : name_(name), imports_(), sessions_()
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

Session *Module::session(std::string name) const
{
    return sessions_.at(name);
}

unsigned int Module::num_session() const
{
    return sessions_.size();
}

void Module::add_session(Session *session)
{
    sessions_.insert({ session->name(), session });
}

bool Module::has_session(std::string name) const
{
    return (sessions_.find(name) != sessions_.end());
}

} // namespace sesstype
