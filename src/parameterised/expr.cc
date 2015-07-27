#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "sesstype/parameterised/expr.h"

namespace sesstype {
namespace parameterised {

// Expr ----------------------------------------------------------------------

Expr::Expr(int type)
{
    type_ = type;
}

int Expr::type() const
{
    return type_;
}

Expr::~Expr()
{
}

// VarExpr -------------------------------------------------------------------

VarExpr::VarExpr(std::string name) : Expr(ST_EXPR_VAR), name_(name)
{
}

VarExpr::VarExpr(const VarExpr &expr) : Expr(ST_EXPR_VAR), name_(expr.name_)
{
}

VarExpr::~VarExpr()
{
}

VarExpr *VarExpr::clone() const
{
    return new VarExpr(*this);
}

std::string VarExpr::name() const
{
    return name_;
}

// ValExpr -------------------------------------------------------------------

ValExpr::ValExpr(int num) : Expr(ST_EXPR_CONST), num_(num)
{
}

ValExpr::ValExpr(const ValExpr &expr) : Expr(ST_EXPR_CONST), num_(expr.num_)
{
}

ValExpr::~ValExpr()
{
}

ValExpr *ValExpr::clone() const
{
    return new ValExpr(*this);
}

int ValExpr::num() const
{
    return num_;
}

// BinExpr -------------------------------------------------------------------

BinExpr::BinExpr(int op, Expr *lhs, Expr *rhs) : Expr(op), lhs_(lhs), rhs_(rhs)
{
}

BinExpr::~BinExpr()
{
    delete lhs_;
    delete rhs_;
}

int BinExpr::op() const
{
    return type();
}

Expr *BinExpr::lhs() const
{
    return lhs_;
}

Expr *BinExpr::rhs() const {
    return rhs_;
}

// AddExpr -------------------------------------------------------------------

AddExpr::AddExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_ADD, lhs, rhs)
{
}

AddExpr::AddExpr(const AddExpr &expr)
    : BinExpr(ST_EXPR_ADD, expr.lhs_, expr.rhs_)
{
}

AddExpr::~AddExpr()
{
}

AddExpr *AddExpr::clone() const
{
    return new AddExpr(*this);
}

bool AddExpr::is_associative() const
{
    return true;
}

bool AddExpr::is_commutative() const
{
    return true;
}

// SubExpr -------------------------------------------------------------------

SubExpr::SubExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SUB, lhs, rhs)
{
}

SubExpr::SubExpr(const SubExpr &expr)
    : BinExpr(ST_EXPR_SUB, expr.lhs_, expr.rhs_)
{
}

SubExpr::~SubExpr()
{
}

SubExpr *SubExpr::clone() const
{
    return new SubExpr(*this);
}

bool SubExpr::is_associative() const
{
    return true;
};

bool SubExpr::is_commutative() const
{
    return false;
}


// MulExpr -------------------------------------------------------------------

MulExpr::MulExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_MUL, lhs, rhs)
{
}

MulExpr::MulExpr(const MulExpr &expr)
    : BinExpr(ST_EXPR_MUL, expr.lhs_, expr.rhs_)
{
}

MulExpr::~MulExpr()
{
}

MulExpr *MulExpr::clone() const
{
    return new MulExpr(*this);
}

bool MulExpr::is_associative() const
{
    return true;
}

bool MulExpr::is_commutative() const
{
    return true;
}

// DivExpr -------------------------------------------------------------------

DivExpr::DivExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_DIV, lhs, rhs)
{
}

DivExpr::DivExpr(const DivExpr &expr)
    : BinExpr(ST_EXPR_DIV, expr.lhs_, expr.rhs_)
{
}

DivExpr *DivExpr::clone() const
{
    return new DivExpr(*this);
}

DivExpr::~DivExpr()
{
}

bool DivExpr::is_associative() const
{
    return true;
};

bool DivExpr::is_commutative() const
{
    return false;
}

// ModExpr -------------------------------------------------------------------

ModExpr::ModExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_MOD, lhs, rhs)
{
}

ModExpr::ModExpr(const ModExpr &expr)
    : BinExpr(ST_EXPR_MOD, expr.lhs_, expr.rhs_)
{
}

ModExpr::~ModExpr()
{
}

ModExpr *ModExpr::clone() const
{
    return new ModExpr(*this);
}

bool ModExpr::is_associative() const
{
    return true;
}

bool ModExpr::is_commutative() const
{
    return false;
}

// ShlExpr -------------------------------------------------------------------

ShlExpr::ShlExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SHL, lhs, rhs)
{
}

ShlExpr::ShlExpr(const ShlExpr &expr)
    : BinExpr(ST_EXPR_SHL, expr.lhs_, expr.rhs_)
{
}

ShlExpr::~ShlExpr()
{
}

ShlExpr *ShlExpr::clone() const
{
    return new ShlExpr(*this);
}

bool ShlExpr::is_associative() const
{
    return false;
}

bool ShlExpr::is_commutative() const
{
    return false;
}

// ShrExpr -------------------------------------------------------------------

ShrExpr::ShrExpr(Expr *lhs, Expr *rhs) : BinExpr(ST_EXPR_SHR, lhs, rhs)
{
}

ShrExpr::ShrExpr(const ShrExpr &expr)
    : BinExpr(ST_EXPR_SHR, expr.lhs_, expr.rhs_)
{
}

ShrExpr::~ShrExpr()
{
}

ShrExpr *ShrExpr::clone() const
{
    return new ShrExpr(*this);
}

bool ShrExpr::is_associative() const
{
    return false;
}

bool ShrExpr::is_commutative() const
{
    return false;
}

// SeqExpr -------------------------------------------------------------------

SeqExpr::SeqExpr() : Expr(ST_EXPR_SEQ), vals_()
{
}

SeqExpr::SeqExpr(const SeqExpr &expr)
    : Expr(ST_EXPR_SEQ), vals_(expr.vals_)
{
}

SeqExpr::~SeqExpr()
{
}

SeqExpr *SeqExpr::clone() const
{
    return new SeqExpr(*this);
}

int SeqExpr::value(unsigned int idx) const
{
    return vals_.at(idx);
}

unsigned int SeqExpr::num_value() const
{
    return vals_.size();
}

void SeqExpr::append_value(int value)
{
    vals_.push_back(value);
}

std::vector<int>::const_iterator SeqExpr::seq_begin() const
{
    return vals_.begin();
}

std::vector<int>::const_iterator SeqExpr::seq_end() const
{
    return vals_.end();
}

// RngExpr -------------------------------------------------------------------

RngExpr::RngExpr(std::string bindvar, Expr *from, Expr *to)
    : Expr(ST_EXPR_RNG), bindvar_(bindvar), from_(from), to_(to)
{
}

RngExpr::RngExpr(Expr *from, Expr *to)
    : Expr(ST_EXPR_RNG), from_(from), to_(to)
{
}

RngExpr::RngExpr(const RngExpr &expr)
    : Expr(ST_EXPR_RNG),
      bindvar_(expr.bindvar_), from_(expr.from_), to_(expr.to_)
{
}

RngExpr::~RngExpr()
{
    delete from_;
    delete to_;
}

RngExpr *RngExpr::clone() const
{
    return new RngExpr(*this);
}

void RngExpr::set_bindvar(std::string bindvar)
{
    bindvar_ = bindvar;
}

std::string RngExpr::bindvar() const
{
    return bindvar_;
}

Expr *RngExpr::from() const
{
    return from_;
}

void RngExpr::set_from(Expr *from)
{
    delete from_;
    from_ = from;
}

Expr *RngExpr::to() const
{
    return to_;
}

void RngExpr::set_to(Expr *to)
{
    delete to_;
    to_ = to;
}

} // namespace parameterised
} // namespace sesstype
