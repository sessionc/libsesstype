#include <sesstype/node.h>

namespace sesstype {

Node::Node(unsigned int type) : type_(type)
{
}

Node::~Node()
{
}

unsigned int Node::type() const
{
    return type_;
}

} // namespace sesstype
