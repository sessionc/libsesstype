/**
 * \file sesstype/import.h
 * \brief Protocol or Module imports.
 */
#ifndef SESSTYPE__IMPORT_H__
#define SESSTYPE__IMPORT_H__

#ifdef __cplusplus
#include <string>
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

/**
 * \brief Import statement.
 */
class Import {
  public:
    /// \brief Import constructor without "from" or alias.
    Import(std::string name);
    /// \brief Import constructor
    /// \param[in] from Module name.
    /// \param[in] as Import alias name.
    Import(std::string name, std::string from, std::string as);

    /// \returns name of Imported Protocol or Module.
    std::string name() const;

    /// \returns name of Protocol or Module imported from.
    std::string from() const;

    /// \returns alias of Protocol or Module imported as.
    std::string as() const;

  private:
    std::string name_;
    std::string from_;
    std::string as_;
};

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __cplusplus
typedef Import st_tree_import_t;
#else
typedef struct Import st_tree_import_t;
#endif

st_tree_import_t *st_mk_import(const char *name);

st_tree_import_t *st_mk_import_from_as(const char *name, const char *from, const char *as);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif
