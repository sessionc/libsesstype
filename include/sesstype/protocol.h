/**
 * \file sesstype/protocol.h
 * \brief A protocol or a session of an interaction, also known in the
 * literature as global type.
 */
#ifndef SESSTYPE__PROTOCOL_H__
#define SESSTYPE__PROTOCOL_H__

#ifdef __cplusplus
#include <string>
#include <unordered_map>
#endif

#include <sesstype/import.h>
#include <sesstype/node.h>
#include <sesstype/role.h>

#ifdef __cplusplus
namespace sesstype {
#endif

#define ST_PROTOCOL_GLOBAL 1
#define ST_PROTOCOL_LOCAL  2

#ifdef __cplusplus
/**
 * \brief Protocol (st_tree) class encapsulates a single protocol.
 *
 * The Protocol class is a container for
 *  - root Node representing the body of Protocol
 *  - Metadata about the Protocol, including Roles in the Protocol
 */
class Protocol {
  public:
    /// Protocol constructor with "default" as Protocol name.
    Protocol();

    /// Protocol constructor.
    /// \param[in] name Protocol name.
    Protocol(std::string name);

    /// Protocol destructor.
    ~Protocol();

    /// \returns name of Protocol.
    std::string name() const;

    /// \param[in] root Node of Protocol body.
    void set_root(Node *root);

    /// \returns root Node of Protocol body.
    Node *root() const;

    /// Perform endpoint projection of Protocol with respect to endpoint Role.
    /// \param[in] role to project for.
    void project(Role *role);

    /// \returns Protocol type (global or local).
    int type() const;

    /// Add a Role as a participant of the Protocol.
    /// \param[in] role to add to this Protocol.
    void add_role(Role *role);

    /// Test if Role is a participant of Protocol.
    /// \param[in] role to look for.
    /// \returns true if role is a Role in the Protocol.
    bool has_role(Role *role) const;

    /// Retrieve a Role from the Protocol by name.
    /// \param[in] name of the Role.
    /// \returns Role named name.
    /// \exception std::out_of_range if not found.
    Role *role(std::string name) const;

  private:
    std::string name_;
    int type_;
    Role *me_; // Localised role (only used in endpoint protocol)
    Node *root_;
    std::unordered_map<std::string, Role *> roles_;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef Protocol st_tree;
#else
typedef struct Protocol st_tree;
#endif

st_tree *st_tree_mk_init(char *name);

void st_tree_add_import(st_tree *const tree, st_tree_import_t import);
void st_tree_add_role(st_tree *tree, const st_role *role);

void st_tree_set_name(st_tree *tree, const char *name);
void st_tree_set_module(st_tree *tree, const char *module);
void st_tree_set_local_name(st_tree *tree, const char *name, const st_role *endpoint_role);

void st_tree_free(st_tree *tree);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__PROTOCOL_H__
