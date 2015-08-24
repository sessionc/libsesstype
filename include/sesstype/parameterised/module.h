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
#include "sesstype/import.h"
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
template <class ImportType, class SessionType, class ConstantType>
class ModuleTmpl : public sesstype::ModuleTmpl<ImportType, SessionType> {
    std::unordered_map<std::string, ConstantType *> consts_;

  public:
    using ConstantContainer = std::unordered_map<std::string, ConstantType *>;

    /// \brief Module constructor with "default" as Module name.
    ModuleTmpl()
        : sesstype::ModuleTmpl<ImportType, SessionType>(), consts_() { }

    /// \brief Module constructor.
    ModuleTmpl(std::string name)
        : sesstype::ModuleTmpl<ImportType, SessionType>(name), consts_() { }

    /// \brief Module destructor.
    virtual ~ModuleTmpl()
    {
        for (auto constant_pair : consts_) {
            delete constant_pair.second;
        }
    }

    /// \param[in] constant to add to Module.
    void add_constant(ConstantType *c)
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
    ConstantType *constant(std::string name) const
    {
        return consts_.at(name);
    }

    typename ConstantContainer::const_iterator const_begin() const
    {
        return consts_.begin();
    }

    typename ConstantContainer::const_iterator const_end() const
    {
        return consts_.end();
    }
};

using Module = ModuleTmpl<sesstype::Import, Session, Constant>;
#endif // __cplusplus

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MODULE_H__
