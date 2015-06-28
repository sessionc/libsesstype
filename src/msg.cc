#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <sesstype/msg.h>

namespace sesstype {

// MsgPayload ----------------------------------------------------------------

MsgPayload::MsgPayload(std::string type) : name_(), type_(type)
{
}

MsgPayload::MsgPayload(std::string name, std::string type)
    : name_(name), type_(type)
{
}

MsgPayload::MsgPayload(const MsgPayload &payload)
    : name_(payload.name_), type_(payload.type_)
{
}

MsgPayload::~MsgPayload()
{
}

std::string MsgPayload::name() const
{
    return name_;
}

std::string MsgPayload::type() const
{
    return type_;
}

// MsgSig --------------------------------------------------------------------

MsgSig::MsgSig(std::string label) : label_(label), payloads_()
{
}

MsgSig::MsgSig(const MsgSig &msgsig) : label_(msgsig.label_), payloads_()
{
    for (auto payload : msgsig.payloads_) {
        payloads_.push_back(new MsgPayload(*payload));
    }
}

MsgSig::~MsgSig()
{
    for (auto payload : payloads_) {
        delete payload;
    }
}

MsgSig *MsgSig::clone() const
{
    return new MsgSig(*this);
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
