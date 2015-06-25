#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <sesstype/message.h>
#include <sesstype/parameterised/expr.h>
#include <sesstype/parameterised/message.h>

namespace sesstype {
namespace parameterised {

// MsgPayload ----------------------------------------------------------------

MsgPayload::MsgPayload(std::string type) : sesstype::MsgPayload(type), param_()
{
}

MsgPayload::MsgPayload(std::string name, std::string type)
    : sesstype::MsgPayload(name, type), param_()
{
}

MsgPayload::MsgPayload(const MsgPayload &payload)
    : sesstype::MsgPayload(payload), param_()
{
    for (const auto &param : param_) {
        param_.push_back(param->clone());
    }
}

MsgPayload::~MsgPayload()
{
    for (Expr *e : param_) {
        delete e;
    }
}

unsigned int MsgPayload::num_dimen() const
{
    return param_.size();
}

void MsgPayload::add_param(Expr *param)
{
    param_.push_back(param);
}

Expr *MsgPayload::operator[](unsigned int idx)
{
    return param_.at(idx);
}

} // namespace parameterised
} // namespace sesstype
