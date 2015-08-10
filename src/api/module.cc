#include <sesstype/module.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_module *st_module_mk_init(const char *name)
{
    return new Module(name);
}

const char *st_module_get_name(st_module *const module)
{
    return module->name().c_str();
}

st_module *st_module_add_tree(st_module *const module, st_tree *tree)
{
    module->add_session(tree);
    return module;
}

st_tree *st_module_get_tree(st_module *const module, const char *name)
{
    return module->session(name);
}

st_tree *st_module_get_tree_at_idx(st_module *const module, unsigned int index)
{
    auto it = module->session_begin();
    for (int i=0; i<index; i++, it++) { /* empty */ }
    return (*it).second;
}

st_module *st_module_import(st_module *const module, st_import *import)
{
    module->add_import(import);
    return module;
}

void st_module_free(st_module *module)
{
    delete module;
}

#ifdef __cplusplus
} // namespace sesstype
#endif
