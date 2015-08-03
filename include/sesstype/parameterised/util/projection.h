#ifndef SESSTYPE__PARAMETERISED__UTIL__PROJECTION_H__
#define SESSTYPE__PARAMETERISED__UTIL__PROJECTION_H__

#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/node/block.h"
#include "sesstype/parameterised/node/interaction.h"
#include "sesstype/parameterised/node/choice.h"
#include "sesstype/parameterised/node/recur.h"
#include "sesstype/parameterised/node/continue.h"
#include "sesstype/parameterised/node/par.h"
#include "sesstype/parameterised/node/nested.h"
#include "sesstype/parameterised/node/interruptible.h"
#include "sesstype/parameterised/node/for.h"
#include "sesstype/parameterised/node/oneof.h"
#include "sesstype/parameterised/node/if.h"
#include "sesstype/parameterised/node/allreduce.h"

#include "sesstype/parameterised/util/node_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
class Projection : public NodeVisitor {
  public:
    virtual void visit(Node *node) override { }
    virtual void visit(BlockNode *node) override { }
    virtual void visit(InteractionNode *node) override { }
    virtual void visit(ChoiceNode *node) override { }
    virtual void visit(RecurNode *node) override { }
    virtual void visit(ContinueNode *node) override { }
    virtual void visit(ParNode *node) override { }
    virtual void visit(NestedNode *node) override { }
    virtual void visit(InterruptibleNode *node) override { }
    virtual void visit(ForNode *node) override { }
    virtual void visit(OneofNode *node) override { }
    virtual void visit(IfNode *node) override { }
    virtual void visit(AllReduceNode *node) override { }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__PROJECTION_H__
