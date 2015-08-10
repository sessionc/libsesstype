#ifndef SESSTYPE__UTIL__VISITOR_TMPL_H__
#define SESSTYPE__UTIL__VISITOR_TMPL_H__
///
/// Visitor implemented with C++11 variadic templating black magic.
///

#ifdef __cplusplus
namespace sesstype {
namespace util {

// Visitor template declaration.
template <typename... Types>
class Visitor;

// Base case.
template <typename T>
class Visitor<T> {
  public:
    virtual void visit(T *visitable) = 0;
};

// Recursive case.
template <typename T, typename... Types>
class Visitor<T, Types...> : public Visitor<Types...> {
  public:
    // Promote functions from base class.
    using Visitor<Types...>::visit;

    virtual void visit(T *visitable) = 0;
};

template <typename T>
class Visitable {
  public:
    virtual void accept(T &visitor) = 0;
};

template <typename T, typename... Types>
class VisitableImpl : public Visitable<Types...> {
  public:
    virtual void accept(Visitor<Types...> &visitor) {
        visitor.visit(static_cast<T &>(*this));
    }
};

} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__VISITOR_TMPL_H__
