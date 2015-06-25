/**
 * \file sesstype/parameterised/msg.h
 * \brief A message for passing between participants (with parameters).
 */
#ifndef SESSTYPE__PARAMETERISED__MESSAGE_H__
#define SESSTYPE__PARAMETERISED__MESSAGE_H__

#ifdef __cplusplus
#include <vector>
#endif

#include "sesstype/msg.h"
#include "sesstype/parameterised/expr.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
#endif

#ifdef __cplusplus
/**
 * \brieff Message Payload.
 */
class MsgPayload : public sesstype::MsgPayload {
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
    /// \returns number of dimensions in MsgPayload.
    unsigned int num_dimen() const;

    /// \brief Add an expression as a new parameter of current MsgPayload.
    /// \param[in] expr to use as new parameter.
    void add_param(Expr *expr);

    /// \brief Get parameter at dimension <tt>idx</tt> using [] notation.
    /// \param[in] idx of the parameter.
    /// \returns expression at idx'th parameter.
    Expr *operator[](unsigned int idx);

  private:
    std::vector<Expr *> param_;
};
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MESSAGE_H__
