/**
 * \file sesstype/msg.h
 * \brief A message for passing between participants.
 */
#ifndef SESSTYPE__MESSAGE_H__
#define SESSTYPE__MESSAGE_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Message Payload.
 *
 * The MsgPayload class contains the parameters to a message (like function
 * arguments). It is a combination of a name (could be an empty string) and the
 * non-empty datatype. The datatypes can have multi-dimensional Expr parameters
 * for representing multi-dimensional arrays.
 */
class MsgPayload {
  public:
    /// \brief MsgPayload constructor with "" (empty string) as MsgPayload name.
    MsgPayload(std::string type);

    /// \brief MsgPayload constructor.
    /// \param[in] name of MsgPayload (identifier).
    /// \param[in] type of MsgPayload (datatype).
    MsgPayload(std::string name, std::string type);

    /// \brief MsgPayload copy constructor.
    MsgPayload(const MsgPayload &payload);

    /// \brief MsgPayload destructor.
    ~MsgPayload();

    /// \returns name of MsgPayload.
    std::string name() const;

    /// \returns datatype of MsgPayload.
    std::string type() const;

  private:
    std::string name_;
    std::string type_;
};

/**
 * \brief Message Signature.
 *
 * The Message Signature class contains an abstraction of a message (for
 * message-passing based interactions), which contains a message label (for
 * identifying messages) and optionally payload types (see MsgPayload).
 */
class MsgSig {
  public:
    /// \brief MsgSig constructor.
    /// \param[in] label of the MsgSig.
    MsgSig(std::string label);

    /// \brief MsgSig copy constructor.
    MsgSig(const MsgSig &msgsig);

    /// \brief MsgSig destructor.
    virtual ~MsgSig();

    /// \brief Make a MsgSig* clone.
    virtual MsgSig *clone() const;

    /// \returns label of the MsgSig.
    std::string label() const;

    /// \returns number of payload paramaters.
    unsigned int num_payload() const;

    /// \returns payload by name.
    MsgPayload *payload(std::string name) const;

    /// \returns payload by positional index.
    MsgPayload *payload(unsigned int idx) const;

    /// \brief Add a payload parameter to current MsgSig.
    /// \param[in] payload to add.
    void add_payload(MsgPayload *payload);

    /// \returns true if payload with name exists.
    bool has_payload(std::string name) const;

  private:
    std::string label_;
    std::vector<MsgPayload *> payloads_;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef MsgSig st_msg;
typedef MsgPayload st_msg_payload;
#else
typedef struct MsgSig st_msg;
typedef struct MsgPayload st_msg_payload;
#endif

/// \param[in] op operator/label of the message.
/// \returns pointer to MsgSig object allocated dynamically.
st_msg *st_msg_mk_init(const char *op);

/// \param[in,out] msg message to modify.
/// \param[in] payload of message to add to message.
st_msg *st_msg_add_payload(st_msg *msg, st_msg_payload *payload);

/// \param[in,out] msg object to destroy.
void st_msg_free(st_msg *msg);

/// \param[in] type of the message payload.
/// \returns pointer to MsgPayload object allocated dynamically.
st_msg_payload *st_msg_payload_mk_init(const char *type);

/// \param[in] name of the message payload.
/// \param[in] type of the message payload.
/// \returns pointer to MsgPayload objected allocated dynamically.
st_msg_payload *st_msg_payload_mk_annotated(const char *name, const char *type);

/// \param[in,out] payload object to destroy.
void st_msg_payload_free(st_msg_payload *payload);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__MESSAGE_H__
