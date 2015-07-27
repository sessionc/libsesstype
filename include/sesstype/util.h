/**
 * \file sesstype/util.h
 * \brief Utility functions for working with Session Types.
 */
#ifndef SESSTYPE__UTIL_H__
#define SESSTYPE__UTIL_H__

#ifdef __cplusplus
#include <stack>
#include <ostream>
#endif

#include "sesstype/node.h"
#include "sesstype/role.h"

#include "sesstype/node/choice.h"
#include "sesstype/node/continue.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/interruptible.h"
#include "sesstype/node/nested.h"
#include "sesstype/node/par.h"
#include "sesstype/node/recur.h"

#include "sesstype/util/node_visitor.h"
#include "sesstype/util/role_visitor.h"

#ifdef __cplusplus
namespace sesstype {
/**
 * \brief Namespace for utilities and non-datastructure classes.
 */
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class Printer : public NodeVisitor, public RoleVisitor {
  public:
    /// \brief Printer constructor with output to std::out as default.
    Printer();

    /// \brief Printer constructor.
    /// \param[in] os output stream.
    Printer(std::ostream &os);

    /// \brief Output prefix based on current line#, indent level and character.
    void prefix();

    void reset_line_num();

    void visit(Node *node) override;
    void visit(BlockNode *node) override;
    void visit(InteractionNode *node) override;
    void visit(RecurNode *node) override;
    void visit(ContinueNode *node) override;
    void visit(ChoiceNode *node) override;
    void visit(ParNode *node) override;
    void visit(NestedNode *node) override;
    void visit(InterruptibleNode *node) override;

    void visit(Role *role) override;

  private:
    std::ostream &os_;
    unsigned int indent_lvl_;
    std::string indent_str_;
    unsigned int line_count_;
};

/**
 * \brief Endpoint projection.
 */
class Projection : public NodeVisitor {
  public:
    Projection(Role *role);

    Node *get_root();

    void visit(Node *node) override;
    void visit(BlockNode *node) override;
    void visit(InteractionNode *node) override;
    void visit(RecurNode *node) override;
    void visit(ContinueNode *node) override;
    void visit(ChoiceNode *node) override;
    void visit(ParNode *node) override;
    void visit(NestedNode *node) override;
    void visit(InterruptibleNode *node) override;

  private:
    Role *project_role_;
    std::stack<Node *> stack_;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL_H__
