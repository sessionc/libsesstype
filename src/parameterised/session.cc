#include <string>
#include <unordered_map>

#include <sesstype/session.h>

#include <sesstype/parameterised/session.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/parameterised/node.h>

namespace sesstype {
/**
 * \brief namespace for parameterised flavour of Session Types.
 */
namespace parameterised {

Session::Session() : sesstype::Session(), groups_()
{
}

Session::Session(std::string name) : sesstype::Session(name), groups_()
{
}

Session::~Session()
{
    for (auto grp_pair : groups_) {
        delete grp_pair.second;
    }
}

RoleGrp *Session::group(std::string name) const
{
    return groups_.at(name);
}

void Session::add_group(RoleGrp *group)
{
  groups_.insert({ group->name(), group });
}

bool Session::has_role_grp(RoleGrp *group) const
{
    return (groups_.find(group->name()) != groups_.end());
}

} // namespace parameterised
} // namespace sesstype
