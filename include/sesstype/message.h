/**
 * \file sesstype/message.h
 * \brief A message for passing between participants.
 */
#ifndef SESSTYPE__MESSAGE_H__
#define SESSTYPE__MESSAGE_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#endif

#include "sesstype/expr.h"

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
    /// MsgPayload constructor with "" (empty string) as MsgPayload name.
    MsgPayload(std::string type);

    /// MsgPayload constructor.
    /// \param[in] name of MsgPayload (identifier).
    /// \param[in] type of MsgPayload (datatype).
    MsgPayload(std::string name, std::string type);

    /// MsgPayload destructor.
    ~MsgPayload();

    /// \returns name of MsgPayload.
    std::string name() const;

    /// \returns datatype of MsgPayload.
    std::string type() const;

    /// \returns number of dimensions in MsgPayload.
    unsigned int num_dimen() const;

    /// Add an expression as a new parameter (dimension) of current MsgPayload.
    /// \param[in] expr to use as new parameter.
    void add_param(Expr *expr);

    /// Get parameter at dimension <tt>idx</tt> using [] notation.
    /// \param[in] idx of the parameter.
    /// \returns expression at idx'th parameter.
    Expr *operator[](unsigned int idx);

  private:
    std::string name_;
    std::string type_;
    std::vector<Expr *> param_;
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
    /// MsgSig constructor.
    /// \param[in] label of the MsgSig.
    MsgSig(std::string label);

    /// MsgSig destructor.
    ~MsgSig();

    /// \returns label of the MsgSig.
    std::string label() const;

    /// \returns number of payload paramaters.
    unsigned int num_payload() const;

    /// \returns payload by name.
    MsgPayload *payload(std::string name) const;

    /// \returns payload by positional index.
    MsgPayload *payload(unsigned int idx) const;

    /// Add a payload parameter to current MsgSig.
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
} // namespace sesstype
#endif

#endif//SESSTYPE__MESSAGE_H__
