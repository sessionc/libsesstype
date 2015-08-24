#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/util/print.h"
#include "sesstype/parameterised/util/project.h"

namespace sesstype {
namespace parameterised {

std::ostream &operator<<(std::ostream &os, Node &node)
{
    sesstype::parameterised::util::PrintVisitor printer(os);
    node.accept(printer);
    return os;
}

void st_param_node_print(st_param_node *const node)
{
    sesstype::parameterised::util::PrintVisitor printer;
    node->accept(printer);
}

st_param_node *st_param_node_project(st_param_node *const node, st_param_role *const endpoint)
{
    sesstype::parameterised::util::ProjectionVisitor proj_visitor(endpoint);
    node->accept(proj_visitor);
    return proj_visitor.get_root();
}

void st_param_node_free(st_param_node *node)
{
    delete node;
}

} // namespace parameterised
} // namespace sesstype
