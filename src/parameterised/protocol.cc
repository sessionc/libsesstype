#include <string>
#include <unordered_map>

#include <sesstype/protocol.h>

#include <sesstype/parameterised/protocol.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/parameterised/node.h>

namespace sesstype {
/**
 * \brief namespace for parameterised flavour of Session Types.
 */
namespace parameterised {

Protocol::Protocol() : sesstype::Protocol(), groups_()
{
}

Protocol::Protocol(std::string name) : sesstype::Protocol(name), groups_()
{
}

Protocol::~Protocol()
{
    for (auto grp_pair : groups_) {
        delete grp_pair.second;
    }
}

RoleGrp *Protocol::group(std::string name) const
{
    return groups_.at(name);
}

void Protocol::add_group(RoleGrp *group)
{
  groups_.insert({ group->name(), group });
}

bool Protocol::has_role_grp(RoleGrp *group) const
{
    return (groups_.find(group->name()) != groups_.end());
}

} // namespace parameterised
} // namespace sesstype
