/**
 * \file sesstype/module.h
 * \brief Module containing protocols or sessions.
 */
#ifndef SESSTYPE__MODULE_H__
#define SESSTYPE__MODULE_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include "sesstype/constant.h"
#include "sesstype/import.h"
#include "sesstype/protocol.h"

#ifdef __cplusplus
/**
 * \brief namespace for Session Types.
 */
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Module is a container class for multiple logically related Protocols.
 */
class Module {
  public:
    /// \brief Module constructor with "default" as Module name.
    Module();

    /// \brief Module constructor.
    Module(std::string name);

    /// \brief Module destructor.
    ~Module();

    /// \returns name of Module.
    std::string name() const;

    /// \brief Replace Module name.
    /// \param[in] name of Module to replace with.
    void set_name(std::string name);

    /// \returns Protocol named <tt>name</tt>.
    /// \exception std::out_of_range if not found.
    Protocol *protocol(std::string name) const;

    /// \returns number of Protocol in Module.
    unsigned int num_protocol() const;

    /// \param[in] protocol to add as component of Module.
    void add_protocol(Protocol *protocol);

    /// \brief Test if Protocol is in Module.
    /// \returns true if <tt>name</tt> is a Protocol in Module.
    bool has_protocol(std::string name) const;

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

    /// \detail This returns the original Import if alias is matched.
    /// \returns Import named (or with alias)<tt>name</tt>.
    /// \exception std::out_of_range if not found.
    Import *import(std::string name) const;

    unsigned int num_import() const;

    /// \brief Test if Import is in Module.
    /// \returns true if <tt>name</tt> is an Import (or alias) in Module.
    bool has_import(std::string name) const;

    /// \param[in] import to add to Module.
    void add_import(Import *import);

  private:
    std::string name_;
    std::unordered_map<std::string, Constant *> consts_;
    std::unordered_map<std::string, std::pair<Import *, bool>> imports_;
    std::unordered_map<std::string, Protocol *> protocols_;
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__MODULE_H__
