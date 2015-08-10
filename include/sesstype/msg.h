/**
 * \file sesstype/msg.h
 * \brief A message for passing between participants.
 */
#ifndef SESSTYPE__MSG_H__
#define SESSTYPE__MSG_H__

#ifdef __cplusplus
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#endif

#include "sesstype/util/clonable.h"

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
class MsgPayload : public util::Clonable {
    std::string name_;
    std::string type_;

  public:
    /// \brief MsgPayload constructor with "" (empty string) as MsgPayload name.
    MsgPayload(std::string type) : name_(), type_(type) { }

    /// \brief MsgPayload constructor.
    /// \param[in] type of MsgPayload (datatype).
    /// \param[in] name of MsgPayload (identifier).
    MsgPayload(std::string type, std::string name)
        : name_(name), type_(type) { }

    /// \brief MsgPayload copy constructor.
    MsgPayload(const MsgPayload &payload)
        : name_(payload.name_), type_(payload.type_) { }

    /// \brief MsgPayload destructor.
    ~MsgPayload() { }

    MsgPayload *clone() const override
    {
        return new MsgPayload(*this);
    }

    /// \returns name of MsgPayload.
    std::string name() const
    {
        return name_;
    }

    /// \returns datatype of MsgPayload.
    std::string type() const
    {
        return type_;
    }

};

/**
 * \brief Message Signature.
 *
 * The Message Signature class contains an abstraction of a message (for
 * message-passing based interactions), which contains a message label (for
 * identifying messages) and optionally payload types (see MsgPayload).
 */
class MsgSig : public util::Clonable {
    std::string label_;
    std::vector<MsgPayload *> payloads_;

  public:
    /// \brief MsgSig constructor.
    /// \param[in] label of the MsgSig.
    MsgSig(std::string label) : label_(label), payloads_() { }

    /// \brief MsgSig copy constructor.
    MsgSig(const MsgSig &msgsig) : label_(msgsig.label_), payloads_()
    {
        for (auto payload : msgsig.payloads_) {
            payloads_.push_back(payload);
        }
    }

    /// \brief MsgSig destructor.
    virtual ~MsgSig()
    {
        for (auto payload : payloads_) {
            delete payload;
        }
    }

    /// \brief Make a MsgSig* clone.
    virtual MsgSig *clone() const override
    {
        return new MsgSig(*this);
    }

    /// \returns label of the MsgSig.
    std::string label() const
    {
        return label_;
    }

    /// \returns number of payload paramaters.
    unsigned int num_payloads() const
    {
        return payloads_.size();
    }

    /// \returns payload by name.
    MsgPayload *payload(std::string name) const
    {
        auto it = std::find_if(payloads_.begin(), payloads_.end(),
            [name](const MsgPayload *const payload)
                -> bool { return payload->name() == name; });
        if (it == payloads_.end()) {
            throw std::out_of_range("Payload "+name+" not found");
        }
        return *it;
    }

    /// \returns payload by positional index.
    MsgPayload *payload(unsigned int idx) const
    {
        return payloads_.at(idx);
    }

    /// \brief Add a payload parameter to current MsgSig.
    /// \param[in] payload to add.
    void add_payload(MsgPayload *payload)
    {
        payloads_.push_back(payload->clone());
    }

    /// \returns true if payload with name exists.
    bool has_payload(std::string name) const
    {
        return (std::find_if(payloads_.begin(), payloads_.end(),
                    [name](const MsgPayload *const payload)
                    -> bool { return payload->name() == name; }) != payloads_.end());
    }
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
st_msg *st_mk_msg(const char *op);

/// \param[in,out] msg message to modify.
/// \param[in] payload of message to add to message.
st_msg *st_msg_add_payload(st_msg *msg, st_msg_payload *payload);

/// \param[in,out] msg object to destroy.
void st_msg_free(st_msg *msg);

/// \param[in] type of the message payload.
/// \returns pointer to MsgPayload object allocated dynamically.
st_msg_payload *st_mk_msg_payload(const char *type);

/// \param[in] type of the message payload.
/// \param[in] name of the message payload.
/// \returns pointer to MsgPayload objected allocated dynamically.
st_msg_payload *st_mk_msg_payload_annotated(const char *type, const char *name);

/// \param[in,out] payload object to destroy.
void st_msg_payload_free(st_msg_payload *payload);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__MSG_H__
