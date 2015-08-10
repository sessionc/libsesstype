/**
 * \file sesstype/module.h
 * \brief Module containing sessions or sessions.
 */
#ifndef SESSTYPE__MODULE_H__
#define SESSTYPE__MODULE_H__

#ifdef __cplusplus
#include <iostream>
#include <string>
#include <unordered_map>
#endif

#include "sesstype/import.h"
#include "sesstype/session.h"

#ifdef __cplusplus
/**
 * \brief namespace for Session Types.
 */
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Module is a container class for multiple logically related Sessions.
 */
class Module {
    std::string name_;
    // Pair<Import * theimport, bool is_alias>
    std::unordered_map<std::string, std::pair<Import *, bool>> imports_;
    std::unordered_map<std::string, Session *> sessions_;

  public:
    /// \brief Module constructor with "default" as Module name.
    Module() : name_("default"), imports_(), sessions_() { }

    /// \brief Module constructor.
    Module(std::string name) : name_(name), imports_(), sessions_() { }

    /// \brief Module destructor.
    virtual ~Module()
    {
        for (auto import_pair : imports_) {
            if (!import_pair.second.second /*alias?*/) {
                delete import_pair.second.first;
            }
        }
    }

    /// \returns name of Module.
    std::string name() const
    {
        return name_;
    }

    /// \brief Replace Module name.
    /// \param[in] name of Module to replace with.
    void set_name(std::string name)
    {
        name_ = name;
    }

    /// \param[in] Session to add as component of Module.
    void add_session(Session *session)
    {
        sessions_.insert(
            std::pair<std::string, Session *>(session->name(), session)
        );
    }

    /// \returns number of Session in Module.
    unsigned int num_session() const
    {
        return sessions_.size();
    }

    /// \brief Test if Session is in Module.
    /// \returns true if <tt>name</tt> is a Session in Module.
    bool has_session(std::string name) const
    {
        return (sessions_.find(name) != sessions_.end());
    }

    /// \returns Session named <tt>name</tt>.
    /// \exception std::out_of_range if not found.
    virtual Session *session(std::string name) const
    {
        return sessions_.at(name);
    }

    /// \param[in] import to add to Module.
    void add_import(Import *import)
    {
        imports_.insert({ import->name(), std::make_pair(import, false)});
        if (import->as() != "") {
            imports_.insert({ import->as(), std::make_pair(import, true/*alias*/)});
        }
    }

    unsigned int num_import() const
    {
        return imports_.size();
    }

    /// \brief Test if Import is in Module.
    /// \returns true if <tt>name</tt> is an Import (or alias) in Module.
    bool has_import(std::string name) const
    {
        return (imports_.find(name) != imports_.end());
    }

    /// \detail This returns the original Import if alias is matched.
    /// \returns Import named (or with alias)<tt>name</tt>.
    /// \exception std::out_of_range if not found.
    virtual Import *import(std::string name) const
    {
        return imports_.at(name).first;
    }
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Module st_module;
#else
typedef struct Module st_module;
#endif

/// \param[in] name of the Module (name can include dots).
/// \returns pointer to Module object allocated dynamically.
st_module *st_module_mk_init(const char *name);

/// \param[in] module to query.
const char *st_module_get_name(st_module *const module);

/// \param[in,out] module to contain tree.
/// \param[in] tree to add.
/// \returns modified module.
st_module *st_module_add_tree(st_module *const module, st_tree *tree);

st_tree *st_module_get_tree(st_module *const module, const char *name);

/// \param[in,out] module to contain import.
/// \param[in] import to add.
/// \returns modified module.
st_module *st_module_import(st_module *const module, st_import *import);

/// \param[in,out] module object to destroy.
void st_module_free(st_module *module);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__MODULE_H__
