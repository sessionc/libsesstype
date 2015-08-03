#ifndef SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
#define SESSTYPE__PARAMETERISED__UTIL__PRINT_H__

#include "sesstype/parameterised/expr.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

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
#include "sesstype/parameterised/util/role_visitor.h"
#include "sesstype/parameterised/util/expr_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class Print : public NodeVisitor, public RoleVisitor, public ExprVisitor {
    std::ostream &os_;
    unsigned int indent_lvl_;
    std::string indent_str_;
    unsigned int line_count_;

  public:
    /// \brief Printer constructor with output to std::out as default.
    Print()
        : os_(std::cout), indent_lvl_(0), indent_str_("  "), line_count_(1) { }

    /// \brief Printer constructor.
    /// \param[in] os output stream.
    Print(std::ostream &os)
        : os_(os), indent_lvl_(0), indent_str_("  "), line_count_(1) { }

    /// \brief Output prefix based on current line#, indent level and character.
    void prefix()
    {
        os_ << line_count_++ << ": ";
        if (indent_lvl_ > 1) {
            os_ << '|';
            for (unsigned int i=1; i<indent_lvl_; i++) {
                os_ << indent_str_;
            }
        }
    }

    void reset_line_num()
    {
        indent_lvl_ = 0;
        line_count_ = 1;
    }

    virtual void visit(Node *node) override
    {
        prefix();
        os_ << "generic {} @ " << node << "\n";
    }

    virtual void visit(InteractionNode *node) override
    {
        prefix();
        os_ << "interaction { from: ";
        if (node->sndr()) {
            node->sndr()->name();
        } else {
            os_ << "(empty)";
        }
        os_ << ", to(" << node->num_rcvrs() << "): [";
        if (node->num_rcvrs() > 0) {
            node->rcvr()->name();
        } else {
            os_ << "(empty)";
        }
        os_ << (node->num_rcvrs()>1 ? ".. ]" : "]")
            << ", msg: " << node->msg()->label()
            << "(" << node->msg()->num_payloads() << ") } @" << node << "\n";
    }

    virtual void visit(BlockNode *node) override
    {
        indent_lvl_++;
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
        indent_lvl_--;
    }

    virtual void visit(RecurNode *node) override
    {
        prefix();
        os_ << "recur " << "{ label: " << node->label() << " }";
        os_ << " children: " << node->num_children() << " @" << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ContinueNode *node) override
    {
        prefix();
        os_ << "cont { label: " << node->label() << " } @" << node << "\n";
    }

    virtual void visit(ChoiceNode *node) override
    {
        prefix();
        os_ << "choice { at: " << node->at()->name() << " }";
        os_ << " children: " << node->num_children() << " @" << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ParNode *node) override
    {
        prefix();
        os_ << "par {}";
        os_ << " parblocks:children: " << node->num_children() << " @" << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(NestedNode *node) override
    {
        prefix();
        os_ << "nested { name: " << node->name();
        os_ << ", scope_name: " << node->scope();
        os_ << ", arg("<< node->num_roleargs() <<"): <";
        for (auto it=node->arg_begin(); it!=node->arg_end(); it++) {
            os_ << (*it)->label() << "(" << (*it)->num_payloads() << ")" << ", ";
        }
        os_ << ">";
        os_ << ", rolearg("<< node->num_args() <<"): [";
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            (*it)->name();
            os_ << ", ";
        }
        os_ << "]} @ " << node << "\n";
    }

    virtual void visit(InterruptibleNode *node) override
    {
        prefix();
        os_ << "interruptible { scope: " << node->scope();
        os_ << " interrupts(" << node->num_interrupts() << "): ";
        for (auto it=node->interrupt_begin(); it!=node->interrupt_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ << ", catches(" << node->num_catches() << "): ";
        for (auto it=node->catch_begin(); it!=node->catch_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ << ", throws(" << node->num_throws() << "): ";
        for (auto it=node->throw_begin(); it!=node->throw_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ <<"} @ " << node << "\n";
    }

    virtual void visit(ForNode *node) override { }
    virtual void visit(OneofNode *node) override { }
    virtual void visit(IfNode *node) override { }
    virtual void visit(AllReduceNode *node) override { }

    virtual void visit(Role *role) override
    {
        os_ << role->name();
    }

    virtual void visit(RoleGrp *role) override { }

    virtual void visit(Expr *expr) override { }
    virtual void visit(VarExpr *expr) override { }
    virtual void visit(ValExpr *expr) override { }
    virtual void visit(AddExpr *expr) override { }
    virtual void visit(SubExpr *expr) override { }
    virtual void visit(MulExpr *expr) override { }
    virtual void visit(DivExpr *expr) override { }
    virtual void visit(ModExpr *expr) override { }
    virtual void visit(ShlExpr *expr) override { }
    virtual void visit(ShrExpr *expr) override { }
    virtual void visit(SeqExpr *expr) override { }
    virtual void visit(RngExpr *expr) override { }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif


#endif//SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
