#ifndef SESSTYPE__NODE_PAR_H__
#define SESSTYPE__NODE_PAR_H__

#include "sesstype/node.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {

class NodeVisitor;

} // namespace util
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Parallel blocks.
 */
class ParNode : public virtual BlockNode {
  public:
    /// \brief ParNode constructor.
    ParNode();

    /// \brief ParNode copy constructor.
    ParNode(const ParNode &node);

    /// \brief ParNode destructor.
    ~ParNode() override;

    /// \brief clone a ParNode.
    ParNode *clone() const override;

    /// \param[in] parallel Node to add as new 'thread'.
    void add_parallel(Node *parallel);

    void accept(util::NodeVisitor &v) override;
};
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
