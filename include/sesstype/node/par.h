#ifndef SESSTYPE__NODE_PAR_H__
#define SESSTYPE__NODE_PAR_H__

#include "sesstype/msg.h"
#include "sesstype/role.h"
#include "sesstype/node.h"
#include "sesstype/node/block.h"

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Parallel blocks.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class ParNodeTmpl : public BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType> {
  public:
    /// \brief ParNode constructor.
    ParNodeTmpl()
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(ST_NODE_PARALLEL) { }

    /// \brief ParNode copy constructor.
    ParNodeTmpl(const ParNodeTmpl &node)
        : BlockNodeTmpl<BaseNode, RoleType, MessageType, VisitorType>(node) { }

    /// \brief clone a ParNode.
    ParNodeTmpl *clone() const override
    {
        return new ParNodeTmpl(*this);
    }

    /// \param[in] parallel Node to add as new 'thread'.
    void add_parallel(BaseNode *par)
    {
        this->append_child(par);
    }

    void accept(VisitorType &v) override;
};

using ParNode = ParNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_par_node_init();
st_node *st_par_node_add_parallel(st_node *node, st_node *par_blk);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE_PAR_H__
