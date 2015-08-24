/**
 * \file sesstype/module.h
 * \brief Module containing sessions or sessions.
 */
#ifndef SESSTYPE__MODULE_H__
#define SESSTYPE__MODULE_H__

#ifdef __cplusplus
#include <string>
#include <iterator>
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
template <class ImportType, class SessionType>
class ModuleTmpl {
    std::string name_;
    // Pair<Import * theimport, bool is_alias>
    std::unordered_map<std::string, std::pair<ImportType *, bool>> imports_;
    std::unordered_map<std::string, SessionType *> sessions_;

  public:
    using ImportContainer  = std::unordered_map<std::string, std::pair<ImportType *, bool>>;
    using SessionContainer = std::unordered_map<std::string, SessionType *>;

    /// \brief Module constructor with "default" as Module name.
    ModuleTmpl() : name_("default"), imports_(), sessions_() { }

    /// \brief Module constructor.
    ModuleTmpl(std::string name) : name_(name), imports_(), sessions_() { }

    /// \brief Module destructor.
    virtual ~ModuleTmpl()
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
    void add_session(SessionType *session)
    {
        sessions_.insert({ session->name(), session });
    }

    /// \returns number of Session in Module.
    unsigned int num_sessions() const
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
    SessionType *session(std::string name) const
    {
        return sessions_.at(name);
    }

    typename SessionContainer::const_iterator session_begin() const
    {
        return sessions_.begin();
    }

    typename SessionContainer::const_iterator session_end() const
    {
        return sessions_.end();
    }

    /// \param[in] import to add to Module.
    void add_import(ImportType *import)
    {
        imports_.insert({ import->name(), std::make_pair(import, false)});
        if (import->as() != "") {
            imports_.insert({ import->as(), std::make_pair(import, true/*alias*/)});
        }
    }

    unsigned int num_imports() const
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
    ImportType *import(std::string name) const
    {
        return imports_.at(name).first;
    }

    typename ImportContainer::const_iterator import_begin() const
    {
        return imports_.begin();
    }

    typename ImportContainer::const_iterator import_end() const
    {
        return imports_.end();
    }
};

using Module = ModuleTmpl<Import, Session>;
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

st_tree *st_module_get_tree_at_idx(st_module *const module, unsigned int index);

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
