/**
 * \file sesstype/parameterised/module.h
 * \brief Module containing protocols or sessions (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__MODULE_H__
#define SESSTYPE__PARAMETERISED__MODULE_H__

#ifdef __cplusplus
#endif

#include "sesstype/module.h"
#include "sesstype/parameterised/constant.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brief Module is a container class for multiple logically related Protocols
 * (contains parameterised elements).
 */
class Module : public sesstype::Module {
  public:
    /// \brief Module constructor with "default" as Module name.
    Module();

    /// \brief Module constructor.
    Module(std::string name);

    /// \brief Module destructor.
    ~Module();

    /// \returns Constant named <tt>name</tt>.
    /// \exception std::out_of_range if not found.
    Constant *constant(std::string name) const;

    /// \returns number of Constant in Module.
    unsigned int num_constant() const;


    /// \brief Test if Constant is in Module.
    /// \returns true if <tt>name</tt> is a Constant in Module.
    bool has_constant(std::string name) const;

    /// \param[in] constant to add to Module.
    void add_constant(Constant *constant);

  private:
    std::unordered_map<std::string, Constant *> consts_;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MODULE_H__
