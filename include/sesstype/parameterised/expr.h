/**
 * \file sesstype/parameterised/expr.h
 * \brief Expressions in a Role parameter or statement.
 */
#ifndef SESSTYPE__PARAMETERISED__EXPR__H__
#define SESSTYPE__PARAMETERISED__EXPR__H__

#ifdef __cplusplus
#include <string>
#include <vector>
#else
#include <stdbool.h>
#include <stdio.h>
#endif

#ifdef __cplusplus
namespace sesstype {

namespace utils {
class ExprVisitor;
} // namespace utils

namespace parameterised {
#endif

#define ST_EXPR_CONST 1
#define ST_EXPR_VAR   2
#define ST_EXPR_ADD   3
#define ST_EXPR_SUB   4
#define ST_EXPR_MUL   5
#define ST_EXPR_DIV   6
#define ST_EXPR_MOD   7
#define ST_EXPR_SHL   8 // <<
#define ST_EXPR_SHR   9 // >>
#define ST_EXPR_SEQ   10 // , (Sequence)
#define ST_EXPR_RNG   11 // .. (Range)

#ifdef __cplusplus

/**
 * \brief Expression.
 */
class Expr {
  public:
    /// \brief Expr destructor.
    virtual ~Expr();

    /// \brief clone an Expr (abstract).
    virtual Expr *clone() const = 0;

    /// \returns type of Expr.
    int type() const;

    /// \brief <tt>accept</tt> method for utils::ExprVisitor.
    virtual void accept(utils::ExprVisitor &v) = 0;

  protected:
    Expr(int type);

  private:
    int type_;
};

/**
 * \brief Variable expression.
 */
class VarExpr : public Expr {
  public:
    /// \brief VarExpr constructor.
    /// \param[in] name of variable.
    VarExpr(std::string name);

    /// \brief VarExpr copy constructor.
    VarExpr(const VarExpr &expr);

    /// \brief VarExpr destructor.
    ~VarExpr() override;

    /// \brief clone a VarExpr.
    VarExpr *clone() const override;

    /// \returns variable name.
    std::string name() const;

    void accept(utils::ExprVisitor &v) override;

  private:
    std::string name_;
};

/**
 * \brief Value expression.
 */
class ValExpr : public Expr {
  public:
    /// \brief ValExpr constructor.
    /// \param[in] num value.
    ValExpr(int num);

    /// \brief ValExpr copy constructor.
    ValExpr(const ValExpr &expr);

    /// \brief ValExpr destructor.
    ~ValExpr() override;

    /// \brief clone a ValExpr.
    ValExpr *clone() const override;

    /// \returns value of expression.
    int num() const;

    void accept(utils::ExprVisitor &v) override;

  private:
    int num_;
};

/**
 * \brief Binary expression (Abstract).
 */
class BinExpr : public Expr {
  public:
    /// \brief BinExpr destructor.
    ~BinExpr() override;

    /// \returns binary operator.
    int op() const;

    /// \returns left Expr.
    Expr *lhs() const;

    /// \return right Expr.
    Expr *rhs() const;

    /// \returns true if binary operator is commutative.
    virtual bool is_commutative() const = 0;

    /// \returns true if binary operator is associative.
    virtual bool is_associative() const = 0;

  protected:
    /// \brief BinExpr constructor.
    BinExpr(int op, Expr *lhs, Expr *rhs);

    Expr *lhs_;
    Expr *rhs_;
};

/**
 * \brief Addition expression.
 */
class AddExpr : public BinExpr {
  public:
    /// \brief AddExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    AddExpr(Expr *lhs, Expr *rhs);

    /// \brief AddExpr copy constructor.
    AddExpr(const AddExpr &expr);

    /// \brief AddExpr destructor.
    ~AddExpr() override;

    /// \brief clone an AddExpr.
    AddExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Subtraction expression.
 */
class SubExpr : public BinExpr {
  public:
    /// \brief SubExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    SubExpr(Expr *lhs, Expr *rhs);

    /// \brief SubExpr copy constructor.
    SubExpr(const SubExpr &expr);

    /// \brief SubExpr destructor.
    ~SubExpr() override;

    /// \brief clone a SubExpr.
    SubExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Multiplication expression.
 */
class MulExpr : public BinExpr {
  public:
    /// \brief MulExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    MulExpr(Expr *lhs, Expr *rhs);

    /// \brief MulExpr copy constructor.
    MulExpr(const MulExpr &expr);

    /// \brief MulExpr destructor.
    ~MulExpr() override;

    /// \brief clone a MulExpr.
    MulExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Division expression.
 */
class DivExpr : public BinExpr {
  public:
    /// \brief DivExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    DivExpr(Expr *lhs, Expr *rhs);

    /// \brief DivExpr copy constructor.
    DivExpr(const DivExpr &expr);

    /// \brief DivExpr destructor.
    ~DivExpr() override;

    /// \brief clone a DivExpr.
    DivExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Modulo expression.
 */
class ModExpr : public BinExpr {
  public:
    /// \brief ModExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ModExpr(Expr *lhs, Expr *rhs);

    /// \brief ModExpr copy constructor.
    ModExpr(const ModExpr &expr);

    /// \brief ModExpr destructor.
    ~ModExpr() override;

    /// \brief clone a ModExpr.
    ModExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Shift left expression.
 */
class ShlExpr : public BinExpr {
  public:
    /// \brief ShlExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ShlExpr(Expr *lhs, Expr *rhs);

    /// \brief ShlExpr copy constructor.
    ShlExpr(const ShlExpr &expr);

    /// \brief ShlExpr destructor.
    ~ShlExpr() override;

    /// \brief clone a ShlExpr.
    ShlExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Shift right expression.
 */
class ShrExpr : public BinExpr {
  public:
    /// \brief ShlExpr constructor.
    /// \param[in] lhs Expr.
    /// \param[in] rhs Expr.
    ShrExpr(Expr *lhs, Expr *rhs);

    /// \brief ShrExpr copy constructor.
    ShrExpr(const ShrExpr &expr);

    /// \brief shrExpr destructor.
    ~ShrExpr() override;

    /// \brief clone a ShrExpr.
    ShrExpr *clone() const override;

    bool is_commutative() const override;

    bool is_associative() const override;

    void accept(utils::ExprVisitor &v) override;
};

/**
 * \brief Value sequence expression
 */
class SeqExpr : public Expr {
  public:
    /// \brief SeqExpr constructor.
    SeqExpr();

    /// \brief SeqExpr copy constructor.
    SeqExpr(const SeqExpr &expr);

    /// \brief SeqExpr destructor.
    ~SeqExpr() override;

    /// \brief clone a SeqExpr.
    SeqExpr *clone() const override;

    /// \returns the idx'th number in the SqeExpr.
    int value(unsigned int idx) const;

    /// \returns number of values in the SeqExpr.
    unsigned int num_value() const;

    /// \brief Append integer value to sequence.
    /// \param[in] value to append.
    void append_value(int value);

    /// \brief Start iterator for sequence.
    std::vector<int>::const_iterator seq_begin() const;

    /// \brief End iterator for sequence.
    std::vector<int>::const_iterator seq_end() const;

    void accept(utils::ExprVisitor &v) override;

  private:
    std::vector<int> vals_;
};

/**
 * \brief Range expression with a binding variable.
 *
 * Specifies a binding variable <tt>bindvar</tt>,
 * a range begin Expr and a range end Expr with default of stride 1.
 */
class RngExpr : public Expr {
  public:
    /// \brief RngExpr constructor with empty bind variable as default.
    /// \param[in] from Expr of RngExpr.
    /// \param[in] to Expr of RngExpr.
    RngExpr(Expr *from, Expr *to);

    /// \brief RngExpr constructor.
    /// \param[in] bindvar name.
    /// \param[in] from Expr of RngExpr.
    /// \param[in] to Expr of RngExpr.
    RngExpr(std::string bindvar, Expr *from, Expr *to);

    /// \brief RngExpr copy constructor.
    RngExpr(const RngExpr &expr);

    /// \brief RngExpr destructor.
    ~RngExpr() override;

    /// \brief clone a RngExpr.
    RngExpr *clone() const override;

    /// \returns bind variable of RngExpr.
    std::string bindvar() const;

    /// Replace bind variable of RngExpr.
    /// \param[in] bindvar to replace with.
    void set_bindvar(std::string bindvar);

    /// \returns from Expr of the range.
    Expr *from() const;

    /// \param[in] from Expr of the range.
    void set_from(Expr *from);

    /// \returns to Expr of the range.
    Expr *to() const;

    /// \param[in] to Expr of the range.
    void set_to(Expr *to);

    void accept(utils::ExprVisitor &v) override;

  private:
    std::string bindvar_;
    Expr *from_;
    Expr *to_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Expr st_expr;        /**< Generic expression. */
typedef BinExpr st_bin_expr; /**< Binary expression. */
typedef SeqExpr st_seq_expr; /**< Sequence [int] expression. */
typedef RngExpr st_rng_expr; /**< Range expression. */
#else
typedef struct Expr st_expr;        /**< Generic expression. */
typedef struct BinExpr st_bin_expr; /**< Binary expression. */
typedef struct SeqExpr st_seq_expr; /**< Sequence [int] expression. */
typedef struct RngExpr st_rng_expr; /**< Range expression. */
#endif // __cplusplus

/// \brief Constructor for value expression.
/// \param[in] num Integer value.
/// \returns expression with constant value (dynamically allocated).
st_expr *st_expr_mk_const(int num);

/// \brief Constructor for variable expression.
/// \param[in] var Variable name.
/// \returns expression with variable (dynamically allocated).
st_expr *st_expr_mk_var(const char *var);

/// \brief Constructor for binary expression.
/// \param[in] left  LHS expression tree.
/// \param[in] type  Expression type as defined in st_node.h (ST_EXPR_TYPE_*)
/// \param[in] right RHS expression tree.
/// \returns expression with binary expression (dynamically allocated).
st_expr *st_expr_mk_binary(st_expr *lhs, int type, st_expr *rhs);

/// \brief Constructor for range expression.
/// \param[in] bindvar Binding variable name, NULL means plain range.
/// \param[in] from    LHS from expression.
/// \param[in] to      RHS to expression.
/// \returns Range exprssion.
st_expr *st_expr_mk_range(char *bindvar, st_expr *from, st_expr *to);

/// \brief Deep copy an expression.
/// \param[in] e Expression to copy.
/// \returns pointer to dynamically allocated copy of expression.
st_expr *st_expr_copy(const st_expr *e);

/// \brief Test if two expressions are identical.
/// \param[in] e0 Expression to compare.
/// \param[in] e1 Expression to compare.
/// \returns true if identical, false otherwise.
bool st_expr_is_identical(st_expr *e0, st_expr *e1);

/// \brief Evaluate an expression.
///
/// Simplify mathematical expressions and return a canonical form if possible.
/// \param[in,out] e Expression to evaluate.
void st_expr_eval(st_expr *e);

/// \brief Free an exprssion.
/// \param[in] e Expression to free.
void st_expr_free(st_expr *e);

/// \brief Apply a relative expression on a binding range.
/// \param[in] b Binding range.
/// \param[in] e Relative expression.
/// \returns pointer to dynamically allocated expression.
st_expr *st_expr_apply(const st_expr *b, const st_expr *e);

/// \brief Invert an expression.
///
/// Currently only work with + - * / expressions and with numeric value on RHS.
/// \param[in] e Expression to invert.
/// \returns an inverted expression or NULL if not possible.
st_expr *st_expr_inv(const st_expr *e);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__H__
