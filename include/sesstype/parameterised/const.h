/**
 * \file sesstype/parameterised/const.h
 * \brief Constants.
 */
#ifndef SESSTYPE__PARAMETERISED__CONST_H__
#define SESSTYPE__PARAMETERISED__CONST_H__

#ifdef __cplusplus
#include <string>
#endif

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#define ST_CONST_VALUE    1
#define ST_CONST_RANGE    2
#define ST_CONST_SCALABLE 3

#ifdef __cplusplus
/**
 * \brief Named constants.
 */
class Constant {
    std::string name_;
    int type_;

  public:
    /// \brief Constant destructor.
    virtual ~Constant() { }

    /// \returns name of Constant.
    std::string name() const
    {
        return name_;
    }

    /// \returns type of Constant.
    int type() const
    {
        return type_;
    }

  protected:
    Constant(std::string name, int type) : name_(name), type_(type) { }
};

/**
 * \brief Constant value.
 */
class ValueConstant : public Constant {
    unsigned int value_;

  public:
    /// \brief ValueConstant constructor.
    /// \param[in] name of ValueConstant.
    /// \param[in] value of ValueConstant.
    ValueConstant(std::string name, unsigned int value)
        : Constant(name, ST_CONST_VALUE), value_(value) { }

    /// \brief ValueConstant destructor.
    ~ValueConstant() override { }

    /// \returns value of ValueConstant.
    unsigned int value() const
    {
        return value_;
    }
};

/**
 * \brief Constant with bounds (range).
 */
class BoundedConstant : public Constant {
    unsigned int lbound_;
    unsigned int ubound_;

  public:
    /// \brief BoundedConstant constructor.
    /// \param[in] name of BoundedConstant.
    /// \param[in] lbound lower bound of range.
    /// \param[in] ubound upper bound of range.
    BoundedConstant(std::string name, unsigned int lbound, unsigned int ubound)
        : Constant(name, ST_CONST_RANGE), lbound_(lbound), ubound_(ubound) { }

    /// \brief BoundedConstant destructor.
    ~BoundedConstant() override { }

    /// \returns lower bound of range.
    unsigned int lbound() const
    {
        return lbound_;
    }

    /// \returns upper bound of range.
    unsigned int ubound() const
    {
        return ubound_;
    }
};

/**
 * \brief Constant with no upper bound (scalable).
 */
class ScalableConstant : public Constant {
    unsigned int lbound_;

  public:
    /// \brief ScalableConstant constructor.
    /// \param[in] name of Constant.
    /// \param[in] lbound lower bound of range.
    ScalableConstant(std::string name, unsigned int lbound)
        : Constant(name, ST_CONST_SCALABLE), lbound_(lbound) { }

    /// \brief ScalableConstant destructor.
    ~ScalableConstant() override { }

    /// \returns lower bound of range.
    unsigned int lbound() const
    {
        return lbound_;
    }
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Constant st_const;
#else
typedef struct Constant st_const;
#endif

/// \brief Make a value constant.
/// \param[in] name of constant.
/// \param[in] value of constant.
/// \returns pointer to allocated Constant object.
st_const *st_mk_val_const(const char *name, int value);

/// \brief Make a range constant.
/// \param[in] name of range constant.
/// \param[in] lbound of range constant.
/// \param[in] ubound of range constant.
/// \returns pointer to allocated Constant object.
st_const *st_mk_rng_const(const char *name, int lbound, int ubound);

/// \brief Make a scalable constant.
/// \param[in] name of scalable constant.
/// \param[in] lbound of range constant.
/// \returns pointer to allocated Constant object.
st_const *st_mk_inf_const(const char *name, int lbound);

/// \brief Get constant type from Constant.
/// \param[in] con Constant to read from.
int st_const_get_type(st_const *const con);

/// \brief Free allocated Constant.
void st_free_const(st_const *con);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif // SESSTYPE__PARAMETERISED__CONST_H__
