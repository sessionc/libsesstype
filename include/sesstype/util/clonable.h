#ifndef SESSTYPE__UTIL__CLONABLE_H__
#define SESSTYPE__UTIL__CLONABLE_H__

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Pure virtual class for clonable classes.
 */
class Clonable {
  public:
    virtual ~Clonable() { }
    virtual Clonable *clone() const = 0;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__CLONABLE_H__
