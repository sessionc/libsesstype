#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <sesstype/expr.h>
#include <sesstype/message.h>

namespace sesstype {

// MsgPayload ----------------------------------------------------------------

MsgPayload::MsgPayload(std::string type) : name_(""), type_(type), param_()
{
}

MsgPayload::MsgPayload(std::string name, std::string type)
    : name_(name), type_(type), param_()
{
}

MsgPayload::~MsgPayload()
{
  for (Expr *e : param_) {
    delete e;
  }
}

std::string MsgPayload::name() const
{
  return name_;
}

std::string MsgPayload::type() const
{
  return type_;
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

// MsgSig --------------------------------------------------------------------

MsgSig::MsgSig(std::string label) : label_(label)
{
}

MsgSig::~MsgSig()
{
  for (auto payload : payloads_) {
    delete payload;
  }
}

std::string MsgSig::label() const
{
  return label_;
}

unsigned int MsgSig::num_payload() const
{
  return payloads_.size();
}

MsgPayload *MsgSig::payload(std::string name) const
{
  auto it = std::find_if(payloads_.begin(), payloads_.end(),
      [name](const MsgPayload *const payload)
        -> bool { return payload->name() == name; });
  if (it == payloads_.end()) {
    throw std::out_of_range("Payload "+name+" not found");
  }
  return *it;
}

MsgPayload *MsgSig::payload(unsigned int idx) const
{
  return payloads_.at(idx);
}

void MsgSig::add_payload(MsgPayload *payload)
{
  payloads_.push_back(payload);
}

bool MsgSig::has_payload(std::string name) const
{
  return (std::find_if(payloads_.begin(), payloads_.end(),
          [name](const MsgPayload *const payload)
            -> bool { return payload->name() == name; }) != payloads_.end());
}

} // namespace sesstype
