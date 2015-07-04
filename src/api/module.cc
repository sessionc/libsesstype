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
    module->add_protocol(tree);
    return module;
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
