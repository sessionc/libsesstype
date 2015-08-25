#ifndef SESSTYPE__PARAMETERISED__UTIL__PROJECT_H__
#define SESSTYPE__PARAMETERISED__UTIL__PROJECT_H__

#ifdef __cplusplus
#include <iostream>
#include <stack>
#endif

#include "sesstype/parameterised/nodes.h"
#include "sesstype/parameterised/role.h"
#include "sesstype/parameterised/role_grp.h"
#include "sesstype/parameterised/util/node_visitor.h"
#include "sesstype/parameterised/util/expr_apply.h"
#include "sesstype/parameterised/util/expr_eval.h"
#include "sesstype/parameterised/util/expr_invert.h"

#ifdef __cplusplus
namespace sesstype {
namespace parameterised {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Endpoint projection for parameterised session types.
 */
class ProjectionVisitor : public NodeVisitor {
    Role *endpoint_;
    std::stack<Node *> stack_;

  public:
    ProjectionVisitor(Role *endpoint) : endpoint_(endpoint), stack_()
    {
        stack_.push(new BlockNode());
    }

    Node *get_root()
    {
        return stack_.top();
    }

    virtual void visit(Node *node) override
    {
        // Nothing.
    }

    virtual void visit(BlockNode *node) override
    {
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
    }

    virtual void visit(sesstype::parameterised::InteractionNode *node) override
    {
        auto *parent = dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top());
        sesstype::parameterised::InteractionNode *projected_node;

        if (endpoint_->num_dimens() == 0) { // Endpoint is non-parameterised

            for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
                if (*it && (*it)->matches(endpoint_)) { // Rule 1.
#ifdef __DEBUG__
                    std::cerr << "Rule 1 Ordinary to\n";
#endif
                    projected_node = node->clone();
                    projected_node->remove_rcvrs();
                    parent->append_child(projected_node);
                    return;
                }
            }

            if (node->sndr()->matches(endpoint_)) { // Rule 2.
#ifdef __DEBUG__
                std::cerr << "Rule 2 Ordinary from\n";
#endif
                projected_node = node->clone();
                projected_node->remove_sndr();
                parent->append_child(projected_node);
                return;
            }
            return;

        } else { // Endpoint is parameterised


            // Parameterised endpoint, so multiple rule matches possible.

            if (node->sndr()->num_dimens() > 0) {

                if (role_is_bindable(node->sndr())) { // Either Rule 8 or 9.

                    for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
                        if (*it && (*it)->matches(endpoint_)) { // Rule 9.
#ifdef __DEBUG__
                            std::cerr << "Rule 9 Relative from\n";
#endif
                            projected_node = node->clone();

                            Role *cond = new Role((*it)->name());
                            Role *sndr = new Role(node->sndr()->name());
                            for (auto param=0; param<node->sndr()->num_dimens(); param++) {
                                Expr *b = (*node->sndr())[param];
                                Expr *e = (**it)[param];
                                std::string bindvar;

                                if (auto b_rng = dynamic_cast<RngExpr *>(b)) {
                                    bindvar = b_rng->bindvar();
                                    util::ExprApply applier(b_rng);
                                    e->accept(applier);
                                    Expr *apply_b_e = applier.apply();
                                    util::ExprEval evaluator;
                                    apply_b_e->accept(evaluator);
                                    Expr *apply_b_e_simplified = evaluator.eval();
                                    delete apply_b_e;

                                    util::ExprInvert inv(bindvar);
                                    e->accept(inv);
                                    Expr *inv_e = inv.invert();

                                    cond->add_param(apply_b_e_simplified);
                                    sndr->add_param(inv_e);
                                } else {
                                    cond->add_param(e);
                                    sndr->add_param(b);
                                }
                            }

                            projected_node->remove_rcvrs();
                            projected_node->set_sndr(sndr);
                            projected_node->set_cond(cond);
                            parent->append_child(projected_node);
                            // Don't return yet.
                        }
                    }

                    if (node->sndr()->matches(endpoint_)) { // Rule 8.
#ifdef __DEBUG__
                        std::cerr << "Rule 8 Relative to\n";
#endif
                        projected_node = node->clone();
                        projected_node->set_cond(projected_node->sndr()->clone());
                        projected_node->remove_sndr();
                        parent->append_child(projected_node);
                        // Don't return yet.
                    }

                } else { // Role not bindable and dimen > 0, Rule 3 or 4.

                    for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
                        if (*it && (*it)->matches(endpoint_)) { // Rule 3.
#ifdef __DEBUG__
                            std::cerr << "Rule 3 Parameterised to\n";
#endif
                            projected_node = node->clone();
                            projected_node->remove_rcvrs();
                            projected_node->set_cond((*it)->clone());
                            parent->append_child(projected_node);
                            // Don't return yet.
                        }
                    }

                    if (node->sndr()->matches(endpoint_)) { // Rule 4
#ifdef __DEBUG__
                        std::cerr << "Rule 4 Parameterised from\n";
#endif
                        projected_node = node->clone();
                        projected_node->set_cond(projected_node->sndr()->clone());
                        projected_node->remove_sndr();
                        parent->append_child(projected_node);
                    }

                }

            } else { // sender dimension == 0, i.e. Group role

                for (auto it=node->rcvr_begin(); it!=node->rcvr_end(); it++) {
                    if (*it && dynamic_cast<RoleGrp *>(*it)) { // Rule 6.
                        if (*it && (*it)->matches(endpoint_)) {
#ifdef __DEBUG__
                            std::cerr << "Rule 6 Group from\n";
#endif
                            projected_node = node->clone();
                            projected_node->remove_rcvrs();
                            projected_node->set_cond((*it)->clone());
                            parent->append_child(projected_node);
                            // Don't return yet.
                        }
                    }
                }

                if (dynamic_cast<RoleGrp *>(node->sndr())) { // Rule 7.
                    if (node->sndr()->matches(endpoint_)) {
#ifdef __DEBUG__
                        std::cerr << "Rule 7 Group to\n";
#endif
                        projected_node = node->clone();
                        projected_node->remove_sndr();
                        projected_node->set_cond(node->sndr()->clone());
                        parent->append_child(projected_node);
                        // Don't return yet.
                    }
                }
            }
        }

    }

    bool role_is_bindable(Role *role)
    {
        for (auto i=0; i<role->num_dimens(); i++) {
            if (dynamic_cast<RngExpr *>((*role)[i])) {
                return true;
            }
        }
        return false;
    }

    virtual void visit(ChoiceNode *node) override
    {
        auto *projected_node = new ChoiceNode(node->at()->clone());

        stack_.push(projected_node);
        if (endpoint_->matches(projected_node->at())) {
            // Choice sender
        }
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    virtual void visit(RecurNode *node) override
    {
        auto *projected_node = new RecurNode(node->label());

        stack_.push(projected_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    virtual void visit(ContinueNode *node) override
    {
        auto *projected_node = new ContinueNode(node->label());

        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }

    virtual void visit(ParNode *node) override
    {
        auto *projected_node = new ParNode();

        stack_.push(projected_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNode *>(stack_.top())->append_child(projected_node);
    }

    virtual void visit(NestedNode *node) override
    {
        // Only include nested node if role arg matches.
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            if ((*it)->matches(endpoint_)) {
                dynamic_cast<BlockNode *>(stack_.top())->append_child(node->clone());
                break;
            }
        }
    }

    virtual void visit(InterruptibleNode *node) override
    {
        auto *new_node = node->clone();

        // TODO only retain interrupts relevant to endpoint role?

        stack_.push(new_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
    }

    virtual void visit(ForNode *node) override
    {
        auto *new_node = node->clone();

        stack_.push(new_node);
        node->BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor>::accept(*this);
        stack_.pop();

        dynamic_cast<BlockNode *>(stack_.top())->append_child(new_node);
    }

    virtual void visit(OneofNode *node) override
    {
        // TODO To be refined.
    }

    virtual void visit(IfNode *node) override
    {
        // Not part of global type syntax.
    }

    virtual void visit(AllReduceNode *node) override
    {
        auto *projected_node = new AllReduceNode(node->msg());
        dynamic_cast<BlockNodeTmpl<Node, Role, MsgSig, util::NodeVisitor> *>(stack_.top())->append_child(projected_node);
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace parameterised
} // namespace sesstype
#endif

#endif//SESSTYPE__PARAMETERISED__UTIL__PROJECT_H__
