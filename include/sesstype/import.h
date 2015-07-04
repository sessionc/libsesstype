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

#ifdef __cplusplus
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
#endif // __cplusplus

#ifdef __cplusplus
extern "C"{
#endif

#ifdef __cplusplus
typedef Import st_import;
#else
typedef struct Import st_import;
#endif

/// \param[in] name of the Import.
/// \returns pointer to Import object allocated dynamically.
st_import *st_import_mk_init(const char *name);

/// \param[in] name of the Import.
/// \param[in] from module of the Import.
/// \param[in] as alias name of the Import.
/// \returns pointer to Import object allocated dynamically.
st_import *st_import_mk_alias(const char *name, const char *from, const char *as);

/// \param[in,out] import object to destroy.
void st_import_free(st_import *import);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif
