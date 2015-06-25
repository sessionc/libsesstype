/**
 * \file parameterised/print.cc
 * \brief Printer.
 */
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>

#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/node.h>
#include <sesstype/parameterised/role.h>
#include <sesstype/parameterised/role_grp.h>
#include <sesstype/utils.h>

namespace sesstype {
namespace utils {

void Printer::visit(parameterised::InteractionNode *node)
{
}

void Printer::visit(parameterised::AllReduceNode *node)
{
    prefix();
    os_ << "allreduce { at: " << node->msgsig() << " }\n";
}

void Printer::visit(parameterised::ForNode *node)
{
    prefix();
    os_ << "for { bind: ";
    node->bind_expr()->accept(*this);
    os_ << " }\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(parameterised::OneofNode *node)
{
    prefix();
    os_ << "oneof { selector_role: ";
    node->selector_role()->accept(*this);
    os_ << "[" << node->selector_role_dimen() << "]";
    os_ << " }\n";

    node->BlockNode::accept(*this);
}

void Printer::visit(parameterised::IfNode *node)
{
    prefix();
    os_ << "if " << std::endl;
    node->BlockNode::accept(*this);
}

// Roles ---------------------------------------------------------------------
//
void Printer::visit(parameterised::Role *role)
{
    os_ << role->name();
    for (auto idx=0; idx<role->num_dimen(); idx++) {
        os_ << "[";
        (*role)[idx]->accept(*this);
        os_ << "]";
    }
}

void Printer::visit(parameterised::RoleGrp *role)
{
    os_ << role->name() << " {";
    for (auto it=role->member_begin(); it!=role->member_end(); it++) {
        (*it).second->accept(*this);
        os_ << ",";
    }
    os_ << "}";
}

// Exprs ---------------------------------------------------------------------

void Printer::visit(parameterised::VarExpr *expr)
{
    os_ << expr->name();
}

void Printer::visit(parameterised::ValExpr *expr)
{
    os_ << expr->num();
}

void Printer::visit(parameterised::AddExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "+";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::SubExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "-";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::MulExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "*";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::DivExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "/";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::ModExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "%";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::ShlExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << "<<";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::ShrExpr *expr)
{
    os_ << "(";
    expr->lhs()->accept(*this);
    os_ << ">>";
    expr->rhs()->accept(*this);
    os_ << ")";
}

void Printer::visit(parameterised::SeqExpr *expr)
{
    std::string seperator("");
    for (auto it=expr->seq_begin(); it!=expr->seq_end(); it++) {
        os_ << seperator << *it;
        seperator = ",";
    }
}

void Printer::visit(parameterised::RngExpr *expr)
{
    os_ << expr->bindvar() << ":";
    expr->from()->accept(*this);
    os_ << "..";
    expr->to()->accept(*this);
}

} // namespace utils

namespace parameterised {

extern "C" {

void st_expr_print(st_expr *expr)
{
    utils::Printer p;
    expr->accept(p);
}

void st_expr_sprint(char **str, st_expr *expr)
{
    std::stringstream ss;
    sesstype::utils::Printer p(ss);
    expr->accept(p);
    *str = (char *)calloc(ss.str().size()+1, sizeof(char));
    strncpy(*str, ss.str().c_str(), ss.str().size());
}

void st_expr_fprint(FILE *stream, st_expr *expr)
{
    std::stringstream ss;
    sesstype::utils::Printer p(ss);
    expr->accept(p);
    fprintf(stream, "%s", ss.str().c_str());
}

} // extern "C"

} // namespace parameterised

} // namespace sesstype
