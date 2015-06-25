#include <sesstype/parameterised/constant.h>

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

st_const_t *st_mk_val_const(const char *name, int value)
{
    return new ValueConstant(name, value);
}

st_const_t *st_mk_rng_const(const char *name, int lbound, int ubound)
{
    return new BoundedConstant(name, lbound, ubound);
}

st_const_t *st_mk_inf_const(const char *name, int lbound)
{
    return new ScalableConstant(name, lbound);
}

int st_const_get_type(st_const_t *const con)
{
    return con->type();
}

void st_free_const(st_const_t *con)
{
    delete con;
}

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif
