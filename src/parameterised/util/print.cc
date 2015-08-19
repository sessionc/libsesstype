#include <ostream>
#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/util/print.h>

namespace sesstype {
namespace parameterised {

std::ostream &operator<<(std::ostream &os, Node &node)
{
    sesstype::parameterised::util::Print p(os);
    node.accept(p);
    return os;
}

std::ostream &operator<<(std::ostream &os, Expr &expr)
{
    sesstype::parameterised::util::Print p(os);
    expr.accept(p);
    return os;
}

} // namespace parameterised
} // namespace sesstype
