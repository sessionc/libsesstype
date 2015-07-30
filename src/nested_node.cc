#include <string>
#include <iterator>
#include <vector>

#include <sesstype/msg.h>
#include <sesstype/node.h>
#include <sesstype/role.h>
#include <sesstype/node/nested.h>

namespace sesstype {

NestedNode::NestedNode(std::string protocol_name)
    : Node(ST_NODE_NESTED),
      name_(protocol_name),
      scope_name_(),
      args_(),
      role_args_()
{
}

NestedNode::NestedNode(std::string protocol_name, std::string scope)
    : Node(ST_NODE_NESTED),
      name_(protocol_name),
      scope_name_(scope),
      args_(),
      role_args_()
{
}

NestedNode::NestedNode(const NestedNode &node)
    : Node(node),
      name_(node.name_),
      scope_name_(node.scope_name_),
      args_(),
      role_args_()
{
    for (auto arg : node.args_) {
        add_arg(arg->clone());
    }
    for (auto role_arg : node.role_args_) {
        add_arg(role_arg->clone());
    }
}

NestedNode::~NestedNode()
{
    for (auto arg : args_) {
        delete arg;
    }
    for (auto role_arg : role_args_) {
        delete role_arg;
    }
}

NestedNode *NestedNode::clone() const
{
    return new NestedNode(*this);
}

std::string NestedNode::name() const
{
    return name_;
}

void NestedNode::set_scope(std::string scope_name)
{
    scope_name_ = scope_name;
}

std::string NestedNode::scope() const
{
    return scope_name_;
}

void NestedNode::add_arg(MsgSig *msg)
{
    args_.push_back(msg);
}

unsigned int NestedNode::num_args() const
{
    return args_.size();
}

MsgSig *NestedNode::arg(unsigned int index) const
{
    return args_.at(index);
}

std::vector<MsgSig *>::const_iterator NestedNode::arg_begin() const
{
    return args_.begin();
}

std::vector<MsgSig *>::const_iterator NestedNode::arg_end() const
{
    return args_.end();
}

void NestedNode::add_arg(Role *role)
{
    role_args_.push_back(role);
}

unsigned int NestedNode::num_roleargs() const
{
    return role_args_.size();
}

Role *NestedNode::rolearg(unsigned int index) const
{
    return role_args_.at(index);
}

std::vector<Role *>::const_iterator NestedNode::rolearg_begin() const
{
    return role_args_.begin();
}

std::vector<Role *>::const_iterator NestedNode::rolearg_end() const
{
    return role_args_.end();
}

} // namespace sesstype
