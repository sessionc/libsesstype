/**
 * \file sesstype/parameterised/module.h
 * \brief Module containing protocols or sessions (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__MODULE_H__
#define SESSTYPE__PARAMETERISED__MODULE_H__

#include "sesstype/module.h"
#include "sesstype/parameterised/const.h"

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
    std::unordered_map<std::string, Constant *> consts_;

  public:
    /// \brief Module constructor with "default" as Module name.
    Module() : sesstype::Module(), consts_() { }

    /// \brief Module constructor.
    Module(std::string name) : sesstype::Module(), consts_() { }

    /// \brief Module destructor.
    virtual ~Module()
    {
        for (auto constant_pair : consts_) {
            delete constant_pair.second;
        }
    }

    virtual Session *session(std::string name) const override
    {
        return dynamic_cast<Session *>(sesstype::Module::session(name));
    }

    /// \returns Constant named <tt>name</tt>.
    /// \exception std::out_of_range if not found.
    Constant *constant(std::string name) const
    {
        return consts_.at(name);
    }

    /// \returns number of Constant in Module.
    unsigned int num_constants() const
    {
        return consts_.size();
    }

    /// \brief Test if Constant is in Module.
    /// \returns true if <tt>name</tt> is a Constant in Module.
    bool has_constant(std::string name) const
    {
        return (consts_.find(name) != consts_.end());
    }

    /// \param[in] constant to add to Module.
    void add_constant(Constant *con)
    {
        consts_.insert({ con->name(), con });
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MODULE_H__
