#ifndef SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
#define SESSTYPE__PARAMETERISED__UTIL__PRINT_H__

#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

#include "sesstype/parameterised/exprs.h"
#include "sesstype/parameterised/nodes.h"

#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"

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
class PrintVisitor : public NodeVisitor, public RoleVisitor, public ExprVisitor {
    std::ostream &os_;
    std::string indent_str_;
    unsigned int indent_lvl_;
    unsigned int line_count_;

  public:
    /// \brief Printer constructor with output to std::out as default.
    PrintVisitor() : os_(std::cout),
              indent_str_("  "),
              indent_lvl_(0),
              line_count_(1) { }

    /// \brief Printer constructor.
    /// \param[in] os output stream.
    PrintVisitor(std::ostream &os) : os_(os),
                              indent_str_("  "),
                              indent_lvl_(0),
                              line_count_(1) { }

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

    void addr(Node *node)
    {
        os_ << " \033[2;33m" << node << "\033[0m";
    }

    void addr(Role *role)
    {
        os_ << "@\033[2;36m" << role << "\033[0m";
    }

    void addr(Expr *expr)
    {
        os_ << " @ \033[2;35m" << expr << "\033[0m";
    }

    virtual void visit(Node *node)
    {
        prefix();
        os_ << "generic {}";
        addr(node);
        os_ << "\n";
    }

    virtual void visit(InteractionNode *node)
    {
        prefix();
        os_ << "interaction";
        addr(node);
        os_ << " { from: ";
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
            << "(" << node->msg()->num_payloads() << ") "
            << ", cond: ";
        if (node->cond()) {
            node->cond()->accept(*this);
        } else {
            os_ << "(none)";
        }
        os_ << " }\n";
    }

    virtual void visit(BlockNode *node)
    {
        if (node->num_children() > 0) {
            prefix();
            os_ << "root";
            addr(node);
            os_ <<" {\n";
            indent_lvl_++;
            for (auto it=node->child_begin(); it!=node->child_end(); it++) {
                (*it)->accept(*this);
            }
            indent_lvl_--;
            prefix();
            os_ << "}\n";
        }
    }

    virtual void visit(RecurNode *node)
    {
        prefix();
        os_ << "recur";
        addr(node);
        os_ <<" { label: " << node->label() << " }";
        os_ << " children: " << node->num_children() << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ContinueNode *node)
    {
        prefix();
        os_ << "cont";
        addr(node);
        os_ << " { label: " << node->label() << " }\n";
    }

    virtual void visit(ChoiceNode *node)
    {
        prefix();
        os_ << "choice";
        addr(node);
        os_ << " { at: ";
        node->at()->accept(*this);
        os_ << ", children: " << node->num_children() << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(ParNode *node)
    {
        prefix();
        os_ << "par";
        addr(node);
        os_ << " {}";
        os_ << " parblocks:children: " << node->num_children() << "\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(NestedNode *node)
    {
        prefix();
        os_ << "nested";
        addr(node);
        os_ << " { name: " << node->name();
        os_ << ", scope: " << node->scope();
        os_ << ", arg("<< node->num_args() <<"): <";
        for (auto it=node->arg_begin(); it!=node->arg_end(); it++) {
            if (it!=node->arg_begin()) {
                os_ << ", ";
            }
            os_ << (*it)->label() << "(" << (*it)->num_payloads() << ")";
        }
        os_ << ">";
        os_ << ", rolearg("<< node->num_roleargs() <<"): [";
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            if (it != node->rolearg_begin()) {
                os_ << ", ";
            }
            (*it)->accept(*this);
        }
        os_ << "]}\n";
    }

    virtual void visit(InterruptibleNode *node)
    {
        prefix();
        os_ << "interruptible";
        addr(node);
        os_ << " { scope: " << node->scope();
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
        os_ <<"}\n";
    }

    virtual void visit(ForNode *node)
    {
        prefix();
        os_ << "for";
        addr(node);
        os_ << " { expr: ";
        node->bindexpr()->accept(*this);
        os_ << " }\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(OneofNode *node)
    {
        prefix();
        os_ << "oneof";
        addr(node);
        os_ << " { range: ";
        node->range()->accept(*this);
        os_ << " , repeat? " << node->is_repeat();
        os_ << " , unordered? " << node->is_unordered();
        os_ << " }\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(IfNode *node)
    {
        prefix();
        os_ << "if";
        addr(node);
        os_ << " { cond: ";
        node->cond()->accept(*this);
        os_ << " }\n";

        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
    }

    virtual void visit(AllReduceNode *node)
    {
        prefix();
        os_ << "allreduce";
        addr(node);
        os_ << " { msg: " << node->msg()->label();
        os_  << "(" << node->msg()->num_payloads() << ") }\n";
    }

    virtual void visit(Role *role)
    {
        os_ << role->name();
        for (int i=0; i<role->num_dimens(); i++) {
            os_ << "[";
            (*role)[i]->accept(*this);
            os_ << "]";
        }
        addr(role);
    }

    virtual void visit(RoleGrp *role)
    {
        os_ << role->name();
        os_ << "{ members#: " << role->num_members() << ", membs: ";
        for (auto it=role->member_begin(); it!=role->member_end(); it++) {
            (*it)->accept(*this);
            os_ << " ";
        }
        os_ << " }";
        addr(role);
    }

    virtual void visit(Expr *expr)
    {
        // Empty.
    }

    virtual void visit(VarExpr *expr)
    {
        os_ << "var(" << expr->name() << ")";
        addr(expr);
    }

    virtual void visit(ValExpr *expr)
    {
        os_ << "val(" << expr->num() << ")";
        addr(expr);
    }

    virtual void visit(AddExpr *expr)
    {
        os_ << "+(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(SubExpr *expr)
    {
        os_ << "-(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(MulExpr *expr)
    {
        os_ << "*(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(DivExpr *expr)
    {
        os_ << "/(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(ModExpr *expr)
    {
        os_ << "%(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(ShlExpr *expr)
    {
        os_ << "<<(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(ShrExpr *expr)
    {
        os_ << ">>(";
        expr->lhs()->accept(*this);
        os_ << " , ";
        expr->rhs()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(SeqExpr *expr)
    {
        os_ << "seq: ";
        for (unsigned int i=0; i<expr->num_values(); i++) {
            if (i != 0) os_ << ",";
            os_ << expr->value(i);
        }
        addr(expr);
    }

    virtual void visit(RngExpr *expr)
    {
        os_ << "rng(" << expr->bindvar() << ",";
        expr->from()->accept(*this);
        os_ << ",";
        expr->to()->accept(*this);
        os_ << ")";
        addr(expr);
    }

    virtual void visit(LogExpr *expr)
    {
        os_ << "log(";
        expr->value()->accept(*this);
        os_ << ", ";
        expr->base()->accept(*this);
        os_ << ")";
        addr(expr);
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__PRINT_H__
