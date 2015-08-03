#ifndef SESSTYPE__UTIL__PRINT_H__
#define SESSTYPE__UTIL__PRINT_H__

#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

#include "sesstype/node.h"
#include "sesstype/node/block.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/choice.h"
#include "sesstype/node/recur.h"
#include "sesstype/node/continue.h"
#include "sesstype/node/par.h"
#include "sesstype/node/nested.h"
#include "sesstype/node/interruptible.h"

#include "sesstype/util/role_visitor.h"
#include "sesstype/util/node_visitor.h"

#ifdef __cplusplus
namespace sesstype {
namespace util {
#endif

#ifdef __cplusplus
/**
 * \brief Protocol and Expression printer.
 */
class Print : public NodeVisitor, public RoleVisitor {
    std::ostream &os_;
    unsigned int indent_lvl_;
    std::string indent_str_;
    unsigned int line_count_;

  public:
    /// \brief Printer constructor with output to std::out as default.
    Print()
        : os_(std::cout), indent_lvl_(0), indent_str_("  "), line_count_(1) { }

    /// \brief Printer constructor.
    /// \param[in] os output stream.
    Print(std::ostream &os)
        : os_(os), indent_lvl_(0), indent_str_("  "), line_count_(1) { }

    /// \brief Output prefix based on current line#, indent level and character.
    void prefix()
    {
        os_ << line_count_++ << ": ";
        if (indent_lvl_ > 1) {
            os_ << '|';
            for (unsigned int i=1; i<indent_lvl_; i++) {
                os_ << indent_str_;
            }
        }
    }

    void reset_line_num()
    {
        indent_lvl_ = 0;
        line_count_ = 1;
    }

    void visit(Node *node)
    {
        prefix();
        os_ << "generic {} @ " << node << "\n";
    }

    void visit(InteractionNode *node)
    {
        prefix();
        os_ << "interaction { from: ";
        if (node->sndr()) {
            node->sndr()->accept(*this);
        } else {
            os_ << "(empty)";
        }
        os_ << ", to(" << node->num_rcvrs() << "): [";
        if (node->num_rcvrs() > 0) {
            node->rcvr()->accept(*this);
        } else {
            os_ << "(empty)";
        }
        os_ << (node->num_rcvrs()>1 ? ".. ]" : "]")
            << ", msg: " << node->msg()->label()
            << "(" << node->msg()->num_payloads() << ") } @" << node << "\n";
    }

    void visit(BlockNode *node)
    {
        std::cout << "Considering a BlockNode\n";
        indent_lvl_++;
        for (auto it=node->child_begin(); it!=node->child_end(); it++) {
            (*it)->accept(*this);
        }
        indent_lvl_--;
    }

    void visit(RecurNode *node)
    {
        prefix();
        os_ << "recur " << "{ label: " << node->label() << " }";
        os_ << " children: " << node->num_children() << " @" << node << "\n";

        dynamic_cast<BlockNode *>(node)->accept(*this);
    }

    void visit(ContinueNode *node)
    {
        prefix();
        os_ << "cont { label: " << node->label() << " } @" << node << "\n";
    }

    void visit(ChoiceNode *node)
    {
        prefix();
        os_ << "choice { at: " << node->at()->name() << " }";
        os_ << " children: " << node->num_children() << " @" << node << "\n";

        dynamic_cast<BlockNode *>(node)->accept(*this);
    }

    void visit(ParNode *node)
    {
        prefix();
        os_ << "par {}";
        os_ << " parblocks:children: " << node->num_children() << " @" << node << "\n";

        dynamic_cast<BlockNode *>(node)->accept(*this);
    }

    void visit(NestedNode *node)
    {
        prefix();
        os_ << "nested { name: " << node->name();
        os_ << ", scope_name: " << node->scope();
        os_ << ", arg("<< node->num_roleargs() <<"): <";
        for (auto it=node->arg_begin(); it!=node->arg_end(); it++) {
            os_ << (*it)->label() << "(" << (*it)->num_payloads() << ")" << ", ";
        }
        os_ << ">";
        os_ << ", rolearg("<< node->num_args() <<"): [";
        for (auto it=node->rolearg_begin(); it!=node->rolearg_end(); it++) {
            (*it)->accept(*this);
            os_ << ", ";
        }
        os_ << "]} @ " << node << "\n";
    }

    void visit(InterruptibleNode *node)
    {
        prefix();
        os_ << "interruptible { scope: " << node->scope();
        os_ << " interrupts(" << node->num_interrupts() << "): ";
        for (auto it=node->interrupt_begin(); it!=node->interrupt_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ << ", catches(" << node->num_catches() << "): ";
        for (auto it=node->catch_begin(); it!=node->catch_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ << ", throws(" << node->num_throws() << "): ";
        for (auto it=node->throw_begin(); it!=node->throw_end(); it++) {
            os_ << (*it).first->name() << "/" << (*it).second->label() << ", ";
        }
        os_ <<"} @ " << node << "\n";
    }

    void visit(Role *role)
    {
        os_ << role->name();
    }
};
#endif // __cplusplus

#ifdef __cplusplus
} // namespace util
} // namespace sesstype
#endif

#endif//SESSTYPE__UTIL__PRINT_H__
