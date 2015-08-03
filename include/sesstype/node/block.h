#ifndef SESSTYPE__NODE__BLOCK_H__
#define SESSTYPE__NODE__BLOCK_H__

#ifdef __cplusplus
#include <vector>
#endif

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Block of statements (Node instances).
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class BlockNodeTmpl : public BaseNode {
    std::vector<BaseNode *> children_;

  public:
    typedef typename std::vector<BaseNode *> NodeContainer;

    /// \brief BlockNode constructor.
    BlockNodeTmpl() : BaseNode(ST_NODE_ROOT), children_() { }

    /// \brief BlockNode copy constructor.
    BlockNodeTmpl(const BlockNodeTmpl &node) : BaseNode(ST_NODE_ROOT), children_()
    {
        for (auto child : node.children_) {
            children_.emplace_back(child);
        }
    }

    /// \brief BlockNode destructor.
    ~BlockNodeTmpl() override
    {
        for (auto node: children_) {
            delete node;
        }
    }

    /// \brief clone a BlockNode.
    BlockNodeTmpl *clone() const override
    {
        return new BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(*this);
    }

    /// \brief Get child Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in BlockNode.
    /// \returns child Node at position <tt>idx</tt>.
    /// \exception std::out_of_range if <tt>idx</tt> is out of bounds.
    BaseNode *child(unsigned int idx) const
    {
        return children_.at(idx);
    }

    /// \brief Get number of child statements (Node) in BlockNode.
    /// \returns number of child Node in current BlockNode.
    unsigned int num_children() const
    {
        return children_.size();
    }

    /// \brief Add child Node to current Block.
    /// \param[in] child Node.
    void append_child(BaseNode *child)
    {
        children_.push_back(child);
    }

    void set_child(unsigned int idx, BaseNode *child)
    {
        children_.at(idx) = child;
    }

    /// \brief Start iterator for children.
    typename NodeContainer::const_iterator child_begin() const
    {
        return children_.begin();
    }

    /// \brief End iterator for children.
    typename NodeContainer::const_iterator child_end() const
    {
        return children_.end();
    }

    virtual void accept(VisitorType &v) override;

  protected:
    BlockNodeTmpl(int type) : BaseNode(type), children_() { }
};

using BlockNode = BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

void st_node_append_child(st_node *parent, st_node *child);

unsigned int st_node_num_children(st_node *parent);

st_node *st_node_get_child(st_node *parent, unsigned int index);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__BLOCK_H__
