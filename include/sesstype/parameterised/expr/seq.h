#ifndef SESSTYPE__PARAMETERISED__EXPR__SEQ_H__
#define SESSTYPE__PARAMETERISED__EXPR__SEQ_H__

#ifdef __cplusplus
#include <iterator>
#include <vector>
#endif

#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Value sequence expression
 */
class SeqExpr : public Expr {
    std::vector<int> vals_;

  public:
    typedef std::vector<int> SequenceContainer;

    /// \brief SeqExpr constructor.
    SeqExpr() : Expr(ST_EXPR_SEQ), vals_() { }

    /// \brief SeqExpr copy constructor.
    SeqExpr(const SeqExpr &expr) : Expr(ST_EXPR_SEQ), vals_(expr.vals_) { }

    /// \brief clone a SeqExpr.
    SeqExpr *clone() const override
    {
        return new SeqExpr(*this);
    }

    /// \returns the idx'th number in the SqeExpr.
    int value(unsigned int idx) const
    {
        return vals_.at(idx);
    }

    /// \returns number of values in the SeqExpr.
    unsigned int num_values() const
    {
        return vals_.size();
    }

    /// \brief Append integer value to sequence.
    /// \param[in] value to append.
    void append_value(int value)
    {
        vals_.push_back(value);
    }

    /// \brief Start iterator for sequence.
    SequenceContainer::const_iterator seq_begin() const
    {
        return vals_.begin();
    }

    /// \brief End iterator for sequence.
    SequenceContainer::const_iterator seq_end() const
    {
        return vals_.end();
    }

    virtual void accept(util::ExprVisitor &v) override;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef SeqExpr st_seq_expr; /**< Sequence [int] expression. */
#else
typedef struct SeqExpr st_seq_expr; /**< Sequence [int] expression. */
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__EXPR__SEQ_H__
