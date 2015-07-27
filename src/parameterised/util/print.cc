/**
 * \file parameterised/util/print.cc
 * \brief Printer.
 */
#include <iostream>
#include <ostream>
#include <sstream>

#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/parameterised/util.h>

#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/node/interaction.h>
#include <sesstype/parameterised/node/choice.h>
#include <sesstype/parameterised/node/recur.h>
#include <sesstype/parameterised/node/continue.h>
#include <sesstype/parameterised/node/par.h>
#include <sesstype/parameterised/node/nested.h>
#include <sesstype/parameterised/node/interruptible.h>
#include <sesstype/parameterised/node/oneof.h>
#include <sesstype/parameterised/node/for.h>
#include <sesstype/parameterised/node/allreduce.h>
#include <sesstype/parameterised/node/if.h>

namespace sesstype {
namespace parameterised {
namespace util {

Printer::Printer()
    : os_(std::cout),
      indent_lvl_(0),
      indent_str_("  "),
      line_count_(1)
{
}

Printer::Printer(std::ostream &os)
    : os_(os),
      indent_lvl_(0),
      indent_str_("  "),
      line_count_(1)
{
}

void Printer::prefix()
{
    os_ << line_count_++ << ": ";
    if (indent_lvl_ > 1) {
        os_ << '|';
        for (int i=1; i<indent_lvl_; i++) {
            os_ << indent_str_;
        }
    }
}

void Printer::reset_line_num()
{
    indent_lvl_ = 0;
    line_count_ = 1;
}

void Printer::visit(Node *node)
{
    prefix();
    os_ << "generic {} @ " << node << "\n";
}

void Printer::visit(InteractionNode *node)
{
    prefix();
    os_ << "interaction { from: ";
    if (node->from()) {
        node->from()->accept(*this);
    } else {
        os_ << "(empty)";
    }
    os_ << ", to(" << node->num_tos() << "): [";
    if (node->num_tos() > 0) {
        node->to()->accept(*this);
    } else {
        os_ << "(empty)";
    }
    os_ << (node->num_tos()>1 ? ".. ]" : "]")
        << ", msgsig: " << node->msgsig()->label()
        << "(" << node->msgsig()->num_payloads() << ") } @" << node << "\n";
}

void Printer::visit(BlockNode *node)
{
    indent_lvl_++;
    for (auto it=node->child_begin(); it!=node->child_end(); it++) {
        (*it)->accept(*this);
    }
    indent_lvl_--;
}

void Printer::visit(RecurNode *node)
{
    prefix();
    os_ << "recur " << "{ label: " << node->label() << " }";
    os_ << " children: " << node->num_children() << " @" << node << "\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(ContinueNode *node)
{
    prefix();
    os_ << "cont { label: " << node->label() << " } @" << node << "\n";
}

void Printer::visit(ChoiceNode *node)
{
    prefix();
    os_  << "choice { at: " << node->at()->name() << " }";
    os_ << " children: " << node->num_children() << " @" << node << "\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(ParNode *node)
{
    prefix();
    os_ << "par {}";
    os_ << " parblocks:children: " << node->num_children() << " @" << node << "\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(NestedNode *node)
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
        (*it)->accept(*this);
        os_ << ", ";
    }
    os_ << "]} @ " << node << "\n";
}

void Printer::visit(InterruptibleNode *node)
{
    prefix();
    os_ << "interruptible { scope_name: " << node->scope();
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

void Printer::visit(AllReduceNode *node)
{
    prefix();
    os_ << "allreduce { at: " << node->msgsig() << " }\n";
}

void Printer::visit(ForNode *node)
{
    prefix();
    os_ << "for { bind: ";
    node->bindexpr()->accept(*this);
    os_ << " } @ " << node<< "\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(OneofNode *node)
{
    prefix();
    os_ << "oneof { selector: ";
    node->selector_role()->accept(*this);
    os_ << "{dim:" << node->selector_dimen() << "}";
    os_ << " } @ " << node << "\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(IfNode *node)
{
    prefix();
    os_ << "if " << std::endl;
    node->BlockNode::accept(*this);
}

void Printer::visit(Role *role)
{
    os_ << role->name();
    for (auto idx=0; idx<role->num_dimen(); idx++) {
        os_ << "[";
        (*role)[idx]->accept(*this);
        os_ << "]";
    }
}

void Printer::visit(RoleGrp *role)
{
    os_ << role->name() << " {";
    for (auto it=role->member_begin(); it!=role->member_end(); it++) {
        (*it).second->accept(*this);
        os_ << ",";
    }
    os_ << "}";
}

void Printer::visit(VarExpr *expr)
{
    os_ << expr->name();
}

void Printer::visit(ValExpr *expr)
{
    os_ << expr->num();
}

void Printer::visit(AddExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "+";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(SubExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "-";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(MulExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "*";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(DivExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "/";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(ModExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "%";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(ShlExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "<<";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(ShrExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << ">>";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(SeqExpr *expr)
{
    std::string seperator("");
    for (auto it=expr->seq_begin(); it!=expr->seq_end(); it++) {
        os_ << seperator << *it;
        seperator = ",";
    }
}

void Printer::visit(RngExpr *expr)
{
    os_ << expr->bindvar() << ":";
    expr->from()->accept(*this);
    os_ << "..";
    expr->to()->accept(*this);
}

} // namespace util
} // namespace parameterised
} // namespace sesstype
