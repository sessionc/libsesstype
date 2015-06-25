/**
 * \file sesstype/parameterised/constant.h
 * \brief Constants.
 */
#ifndef SESSTYPE__PARAMETERISED__CONSTANT_H__
#define SESSTYPE__PARAMETERISED__CONSTANT_H__

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
  public:
    /// \returns name of Constant.
    std::string name() const;

    /// \returns type of Constant.
    int type() const;

    /// \brief Constant destructor.
    virtual ~Constant();

  protected:
    Constant(std::string name, int type);

  private:
    std::string name_;
    int type_;
};

/**
 * \brief Constant value.
 */
class ValueConstant : public Constant {
  public:
    /// \brief ValueConstant constructor.
    /// \param[in] name of ValueConstant.
    /// \param[in] value of ValueConstant.
    ValueConstant(std::string name, int value);

    /// \brief ValueConstant destructor.
    ~ValueConstant() override;

    /// \returns value of ValueConstant.
    int value() const;

  private:
    int value_;
};

/**
 * \brief Constant with bounds (range).
 */
class BoundedConstant : public Constant {
  public:
    /// \brief BoundedConstant constructor.
    /// \param[in] name of BoundedConstant.
    /// \param[in] lbound lower bound of range.
    /// \param[in] ubound upper bound of range.
    BoundedConstant(std::string name, int lbound, int ubound);

    /// \brief BoundedConstant destructor.
    ~BoundedConstant() override;

    /// \returns lower bound of range.
    int lbound() const;

    /// \returns upper bound of range.
    int ubound() const;

  protected:
    int lbound_;
    int ubound_;
};

/**
 * \brief Constant with no upper bound (scalable).
 */
class ScalableConstant : public Constant {
  public:
    /// \brief ScalableConstant constructor.
    /// \param[in] name of Constant.
    /// \param[in] lbound lower bound of range.
    ScalableConstant(std::string name, int lbound);

    /// \brief ScalableConstant destructor.
    ~ScalableConstant() override;

    /// \returns lower bound of range.
    int lbound() const;

  private:
    int lbound_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Constant st_const_t;
#else
typedef struct Constant st_const_t;
#endif

/// \brief Make a value constant.
/// \param[in] name of constant.
/// \param[in] value of constant.
/// \returns pointer to allocated Constant object.
st_const_t *st_mk_val_const(const char *name, int value);

/// \brief Make a range constant.
/// \param[in] name of range constant.
/// \param[in] lbound of range constant.
/// \param[in] ubound of range constant.
/// \returns pointer to allocated Constant object.
st_const_t *st_mk_rng_const(const char *name, int lbound, int ubound);

/// \brief Make a scalable constant.
/// \param[in] name of scalable constant.
/// \param[in] lbound of range constant.
/// \returns pointer to allocated Constant object.
st_const_t *st_mk_inf_const(const char *name, int lbound);

/// \brief Get constant type from Constant.
/// \param[in] con Constant to read from.
int st_const_get_type(st_const_t *const con);

/// \brief Free allocated Constant.
void st_free_const(st_const_t *con);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif // SESSTYPE__PARAMETERISED__CONSTANT_H__
