/**
 * \file sesstype/parameterised/msg.h
 * \brief A message for passing between participants (parameterised).
 */
#ifndef SESSTYPE__PARAMETERISED__MSG_H__
#define SESSTYPE__PARAMETERISED__MSG_H__

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
    std::vector<Expr *> param_;

  public:
    /// \brief MsgPayload constructor with "" (empty string) as MsgPayload name.
    MsgPayload(std::string type) : sesstype::MsgPayload(type), param_() { }

    /// \brief MsgPayload constructor.
    /// \param[in] type of MsgPayload (datatype).
    /// \param[in] name of MsgPayload (identifier).
    MsgPayload(std::string type, std::string name)
        : sesstype::MsgPayload(type, name), param_() { }

    /// \brief MsgPayload copy constructor.
    MsgPayload(const MsgPayload &payload)
        : sesstype::MsgPayload(payload), param_()
    {
        for (auto param : param_) {
            param_.emplace_back(param);
        }
    }

    /// \brief MsgPayload destructor.
    ~MsgPayload()
    {
        for (auto param : param_) {
            delete param;
        }
    }

    /// \returns number of dimensions in MsgPayload.
    unsigned int num_dimens() const
    {
        return param_.size();
    }

    /// \brief Add an expression as a new parameter of current MsgPayload.
    /// \param[in] expr to use as new parameter.
    void add_param(Expr *param)
    {
        param_.push_back(param);
    }

    /// \brief Get parameter at dimension <tt>idx</tt> using [] notation.
    /// \param[in] idx of the parameter.
    /// \returns expression at idx'th parameter.
    Expr *operator[](unsigned int idx)
    {
        return param_.at(idx);
    }
};

using MsgSig = sesstype::MsgSig;
#endif

#ifdef __cplusplus
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__MSG_H__
