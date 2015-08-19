#include <ostream>
#include <sesstype/node.h>
#include <sesstype/util/print.h>

namespace sesstype {

std::ostream &operator<<(std::ostream &os, Node &node)
{
    util::Print p(os);
    node.accept(p);
    return os;
}

} // namespace sesstype
