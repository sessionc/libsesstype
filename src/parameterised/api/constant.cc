#include <sesstype/parameterised/const.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

st_const *st_mk_val_const(const char *name, int value)
{
    return new ValueConstant(name, value);
}

st_const *st_mk_rng_const(const char *name, int lbound, int ubound)
{
    return new BoundedConstant(name, lbound, ubound);
}

st_const *st_mk_inf_const(const char *name, int lbound)
{
    return new ScalableConstant(name, lbound);
}

int st_const_get_type(st_const *const con)
{
    return con->type();
}

void st_free_const(st_const *con)
{
    delete con;
}

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
