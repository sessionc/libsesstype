#ifndef SESSTYPE__PARAMETERISED__NODE__IF_H__
#define SESSTYPE__PARAMETERISED__NODE__IF_H__

#include "sesstype/util/node_visitor.h"

#include "sesstype/parameterised/cond.h"
#include "sesstype/parameterised/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief If-block.
 */
class IfNode : public BlockNode {
  public:
    /// \brief IfNode constructor.
    /// \param[in] cond for the if-block.
    IfNode(MsgCond *cond);

    /// \brief IfNode copy constructor.
    IfNode(const IfNode &node);

    /// \brief IfNode destructor.
    ~IfNode() override;

    /// \brief clone a IfNode.
    IfNode *clone() const override;

    /// \brief Get body Node at position <tt>idx</tt>.
    /// \param[in] idx of Node in IfNode.
    /// \returns body Node at position <tt>idx</tt>
    /// \exception std::out_of_range if <tt>idx</tt> is out of bounds.
    Node *body(unsigned int idx) const;

    /// \brief Add body Node to current if-block
    /// \param[in] body Node.
    void append_body(Node *body);

    /// \returns if-block condition.
    MsgCond *cond() const;

    /// \brief Set if-block condition.
    /// \param[in] cond for the if-block.
    void set_cond(MsgCond *cond);

    void accept(sesstype::util::NodeVisitor &v) override;

  private:
    MsgCond *cond_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_if_node(st_cond *cond);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__NODE__IF_H__
