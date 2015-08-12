/**
 * \file sesstype/parameterised/module.h
 * \brief Module containing protocols or sessions (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__MODULE_H__
#define SESSTYPE__PARAMETERISED__MODULE_H__

#ifdef __cplusplus
#include <iterator>
#include <unordered_map>
#endif

#include "sesstype/module.h"
#include "sesstype/parameterised/const.h"
#include "sesstype/parameterised/session.h"

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
    typedef std::unordered_map<std::string, Constant *> ConstantContainer;

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
        return dynamic_cast<sesstype::parameterised::Session *>(sesstype::Module::session(name));
    }

    /// \param[in] constant to add to Module.
    void add_constant(Constant *c)
    {
        consts_.insert({ c->name(), c });
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

    /// \returns Constant named <tt>name</tt>.
    /// \exception std::out_of_range if not found.
    Constant *constant(std::string name) const
    {
        return consts_.at(name);
    }

    ConstantContainer::const_iterator const_begin() const
    {
        return consts_.begin();
    }

    ConstantContainer::const_iterator const_end() const
    {
        return consts_.end();
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MODULE_H__
