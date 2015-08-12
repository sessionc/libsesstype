#ifndef SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
#define SESSTYPE__PARAMETERISED__UTIL__PRINT_H__

#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

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
        if (line_count_ == 1) {
            os_ << "Line\t |\tTree\n====================\n";
        }
        os_ << line_count_++ << "\t ";
        if (indent_lvl_ > 0) {
            os_ << '|';
            for (unsigned int i=0; i<indent_lvl_; i++) {
                os_ << indent_str_;
            }
        }
    }

    void reset_line_num()
    {
        indent_lvl_ = 0;
        line_count_ = 1;
    }

    virtual void visit(Node *node)
    {
        prefix();
        os_ << "generic {} @ " << node << "\n";
    }

    virtual void visit(InteractionNode *node)
    {
        prefix();
        os_ << "interaction { from: ";
        if (node->sndr()) {
            node->sndr()->accept(*this);
        } else {
            os_ << "(empty)";
        }
        os_ << ", to(" << node->num_rcvrs() << "): [";
        if (node->num_rcvrs() > 0) {
            node->rcvr()->accept(*this);
        } else {
            os_ << "(empty)";
        }
        os_ << (node->num_rcvrs()>1 ? ".. ]" : "]")
            << ", msg: " << node->msg()->label()
            << "(" << node->msg()->num_payloads() << ") } @ " << node << "\n";
    }

    virtual void visit(BlockNode *node)
    {
        prefix();
        os_ << "root @ " << node << " {\n";
        indent_lvl_++;
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
        indent_lvl_--;
        prefix();
        os_ << "}\n";
    }

    virtual void visit(RecurNode *node)
    {
        prefix();
        os_ << "recur " << "{ label: " << node->label() << " }";
        os_ << " children: " << node->num_children() << " @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ContinueNode *node)
    {
        prefix();
        os_ << "cont { label: " << node->label() << " } @ " << node << "\n";
    }

    virtual void visit(ChoiceNode *node)
    {
        prefix();
        os_ << "choice { at: ";
        node->at()->accept(*this);
        os_ << ", children: " << node->num_children() << " @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ParNode *node)
    {
        prefix();
        os_ << "par {}";
        os_ << " parblocks:children: " << node->num_children() << " @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(NestedNode *node)
    {
        prefix();
        os_ << "nested { name: " << node->name();
        os_ << ", scope: " << node->scope();
        os_ << ", arg("<< node->num_args() <<"): <";
        for (auto it=node->arg_begin(); it!=node->arg_end(); it++) {
            os_ << (*it)->label() << "(" << (*it)->num_payloads() << ")" << ", ";
        }
        os_ << ">";
        os_ << ", rolearg("<< node->num_roleargs() <<"): [";
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            (*it)->accept(*this);
            os_ << ", ";
        }
        os_ << "]} @ " << node << "\n";
    }

    virtual void visit(InterruptibleNode *node)
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

    virtual void visit(ForNode *node)
    {
        prefix();
        os_ << "for { expr: ";
        node->bindexpr()->accept(*this);
        os_ << " } @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(OneofNode *node)
    {
        prefix();
        os_ << "oneof { range: ";
        node->range()->accept(*this);
        os_ << " , repeat? " << node->is_repeat();
        os_ << " , unordered? " << node->is_unordered();
        os_ << " } @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(IfNode *node)
    {
        prefix();
        os_ << "if { cond: ";
        node->cond()->accept(*this);
        os_ << " } @ " << node << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(AllReduceNode *node)
    {
        prefix();
        os_ << "allreduce { msg: " << node->msg()->label()
            << "(" << node->msg()->num_payloads() << ") } @ " << node << "\n";
    }

    virtual void visit(Role *role)
    {
        os_ << role->name();
        if (role->num_dimen() > 0) {
            os_ << "[";
            (*role)[0]->accept(*this);
            for (int i=1; i<role->num_dimen(); i++) {
                os_ << "][";
                (*role)[i]->accept(*this);
            }
            os_ << "]";
        }
        os_ << " @ " << role;
    }

    virtual void visit(RoleGrp *role)
    {
        os_ << role->name();
        os_ << "{ members#: " << role->num_members() << ", membs: ";
        for (auto it=role->member_begin(); it!=role->member_end(); it++) {
            (*it).second->accept(*this);
            os_ << " ";
        }
        os_ << " } @ " << role;
    }

    virtual void visit(Expr *expr)
    {
        // Empty.
    }

    virtual void visit(VarExpr *expr)
    {
        os_ << expr->name();
    }

    virtual void visit(ValExpr *expr)
    {
        os_ << expr->num();
    }

    virtual void visit(AddExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << "+";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(SubExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << "-";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(MulExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "*";
        expr->rhs()->accept(*this);
    }

    virtual void visit(DivExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "/";
        expr->rhs()->accept(*this);
    }

    virtual void visit(ModExpr *expr)
    {
        expr->lhs()->accept(*this);
        os_ << "%";
        expr->rhs()->accept(*this);
    }

    virtual void visit(ShlExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << "<<";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(ShrExpr *expr)
    {
        os_ << "(";
        expr->lhs()->accept(*this);
        os_ << ">>";
        expr->rhs()->accept(*this);
        os_ << ")";
    }

    virtual void visit(SeqExpr *expr)
    {
        for (unsigned int i=0; i<expr->num_values(); i++) {
            os_ << expr->value(i) << ",";
        }
    }

    virtual void visit(RngExpr *expr)
    {
        os_ << expr->bindvar() << ":";
        os_ << expr->from();
        expr->from()->accept(*this);
        os_ << "..";
        os_ << expr->to();
        expr->to()->accept(*this);
        os_.flush();
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
#endif

#ifdef __cplusplus
extern "C" {
#endif

void st_param_node_print(st_param_node *node);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
