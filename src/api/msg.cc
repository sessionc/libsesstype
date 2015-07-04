#include <sesstype/msg.h>

#ifdef __cplusplus
namespace sesstype {
#endif

st_msg *st_msg_mk_init(const char *op)
{
    return new MsgSig(op);
}

st_msg *st_msg_add_payload(st_msg *msg, st_msg_payload *payload)
{
    msg->add_payload(payload);
    return msg;
}

void st_msg_free(st_msg *msg)
{
    delete msg;
}

st_msg_payload *st_msg_payload_mk_init(const char *type)
{
    return new MsgPayload(type);
}

st_msg_payload *st_msg_payload_mk_annotated(const char *name, const char *type)
{
    return new MsgPayload(name, type);
}

void st_msg_payload_free(st_msg_payload *payload)
{
    delete payload;
}

#ifdef __cplusplus
} // namespace sesstype
#endif
