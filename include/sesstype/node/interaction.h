#ifndef SESSTYPE__NODE__INTERACTION_H__
#define SESSTYPE__NODE__INTERACTION_H__

#ifdef __cplusplus
#include <vector>
#endif

#include "sesstype/msg.h"
#include "sesstype/node.h"
#include "sesstype/role.h"
#include "sesstype/util/clonable.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
class NodeVisitor;
} // namesapce util
} // namespace sesstype
#endif

#ifdef __cplusplus
namespace sesstype {
#endif

#ifdef __cplusplus
/**
 * \brief Interaction (message-passing) statements.
 *
 * InteractionNode also encapsulates send-only and receive-only statements.
 */
template <class BaseNode, class RoleType, class MessageType, class VisitorType>
class InteractionNodeTmpl : public BaseNode {
    MessageType *msg_;
    RoleType *sndr_;
    std::vector<RoleType *> rcvrs_;

  public:
    typedef typename std::vector<RoleType *> RoleContainer;

    /// \brief InteractionNode constructor with empty MsgSig.
    InteractionNodeTmpl()
        : BaseNode(ST_NODE_SENDRECV),
          msg_(new MessageType("")), sndr_(nullptr), rcvrs_() { }

    /// \brief InteractionNode constructor.
    /// \param[in] msgsig for the interaction.
    InteractionNodeTmpl(MessageType *msg)
        : BaseNode(ST_NODE_SENDRECV),
          msg_(msg->clone()), sndr_(nullptr), rcvrs_() { }

    /// \brief InteractionNode copy constructor.
    InteractionNodeTmpl(const InteractionNodeTmpl &node)
        : BaseNode(ST_NODE_SENDRECV),
          msg_(node.msg_->clone()), sndr_(node.sndr_->clone()), rcvrs_()
    {
        for (auto rcvr : node.rcvrs_) {
            rcvrs_.push_back(rcvr->clone());
        }
    }

    /// \brief InteractionNode destructor.
    ~InteractionNodeTmpl() override
    {
        delete msg_;
        delete sndr_;
        for (auto rcvr : rcvrs_) {
            delete rcvr;
        }
        rcvrs_.clear();
    }

    /// \brief clone a InteractionNode.
    InteractionNodeTmpl *clone() const override
    {
        return new InteractionNodeTmpl(*this);
    }

    /// \brief Replace Msgsig of InteractionNode.
    /// \param[in] msgsig of InteractionNode to replace with.
    void set_msg(MessageType *msg)
    {
        delete msg_;
        msg_ = msg->clone();
    }

    /// \returns message signature of InteractionNode.
    MessageType *msg() const { return msg_; }

    /// \param[in] from Role of InteractionNode.
    void set_sndr(RoleType *sndr)
    {
        delete sndr_;
        sndr_ = sndr->clone();
    }

    /// \returns <tt>from</tt> Role of InteractionNode.
    RoleType *sndr() const { return sndr_; }

    /// \brief Remove from Role.
    void remove_sndr()
    {
        delete sndr_;
        sndr_ = nullptr;
    }

    /// \param[in] to Role to add to this InteractionNode.
    void add_rcvr(RoleType *rcvr) { rcvrs_.push_back(rcvr->clone()); }

    /// \returns number of <tt>to</tt> Role.
    unsigned int num_rcvrs() const { return rcvrs_.size(); }

    /// \brief Convenient function to return the first <tt>to</tt> Role.
    /// \returns the first <tt>to</tt> Role of InteractionNode.
    RoleType *rcvr() const { return rcvrs_.at(0); }

    /// \returns <tt>index</tt>th <tt>to</tt> Role of InteractionNode.
    RoleType *rcvr(unsigned int idx) const { return rcvrs_.at(idx); }

    /// \brief Remove to Role (all of them);
    void clear_rcvrs()
    {
        for (auto *rcvr : rcvrs_) {
            delete rcvr;
        }
        rcvrs_.clear();
    }

    /// \brief Start iterator for to Role.
    typename RoleContainer::const_iterator rcvr_begin() const
    {
        return rcvrs_.begin();
    }

    /// \brief End iterator for to Role.
    typename RoleContainer::const_iterator rcvr_end() const
    {
        return rcvrs_.end();
    }

    void accept(VisitorType &v) override;
};

using InteractionNode = InteractionNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>;
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif

st_node *st_mk_interaction_node_init();

st_node *st_mk_interaction_node(st_msg *msg);

st_node *st_interaction_node_set_msg(st_node *const node, st_msg *msg);

st_msg *st_interaction_node_get_msg(st_node *const node);

st_node *st_interaction_node_set_from(st_node *const node, st_role *from);

st_role *st_interaction_node_get_from(st_node *const node);

st_node *st_interaction_node_add_to(st_node *const node, st_role *to);

unsigned int st_interaction_node_num_tos(st_node *const node);

st_role **st_interaction_node_get_tos(st_node *const node);

st_role *st_interaction_node_get_to(st_node *const node, unsigned int index);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
} // namespace sesstype
#endif

#endif//SESSTYPE__NODE__INTERACTION_H__
