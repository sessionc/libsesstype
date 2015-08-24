#include <iostream>

#include "sesstype/node.h"
#include "sesstype/util/print.h"
#include "sesstype/util/project.h"

namespace sesstype {

st_node *st_node_project(st_node *const node, st_role *const endpoint)
{
    sesstype::util::ProjectionVisitor proj_visitor(endpoint);
    node->accept(proj_visitor);
    return proj_visitor.get_root();
}

void st_node_print(st_node *const node)
{
    sesstype::util::Print printer;
    node->accept(printer);
}

std::ostream &operator<<(std::ostream &os, Node &node)
{
    util::Print p(os);
    node.accept(p);
    return os;
}
void st_node_free(st_node *node)
{
    delete node;
}

} // namespace sesstype
