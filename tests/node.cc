/**
 * \file test/node.cc
 * \brief Tests for sesstype::Node.
 */

#include "gtest/gtest.h"

#include <string>

#include "sesstype/msg.h"
#include "sesstype/node.h"
#include "sesstype/role.h"
#include "sesstype/parameterised/expr.h"
#include "sesstype/parameterised/node.h"
#include "sesstype/parameterised/role.h"

namespace sesstype {
namespace tests {

class NodeTest : public ::testing::Test {
 protected:
  NodeTest() {}
};

/**
 * \test BlockNode operations.
 */
TEST_F(NodeTest, TestBlockNode)
{
    auto *node = new sesstype::InteractionNode();
    node->set_from(new Role("Alice"));
    node->add_to(new Role("Bob"));
    auto *node2 = new sesstype::InteractionNode();
    node->set_from(new Role("Bob"));
    node->add_to(new Role("Carol"));
    auto *node3 = new sesstype::InteractionNode();
    node->set_from(new Role("Bob"));
    node->add_to(new Role("Alice"));

    auto *blk = new sesstype::BlockNode();
    EXPECT_EQ(blk->type(), ST_NODE_ROOT);
    EXPECT_EQ(blk->num_child(), 0);
    blk->append_child(node);
    EXPECT_EQ(blk->num_child(), 1);
    EXPECT_EQ(blk->child(0), node);
    blk->append_child(node2);
    EXPECT_EQ(blk->num_child(), 2);
    EXPECT_EQ(blk->child(1), node2);
    blk->append_child(node3);
    EXPECT_EQ(blk->num_child(), 3);
    EXPECT_EQ(blk->child(2), node3);

    int idx=0;
    for (auto it=blk->child_begin(); it!=blk->child_end(); it++, idx++) {
        EXPECT_EQ(blk->child(idx), *it);
    }
    delete blk;
}

/**
 * \test InteractionNode operations.
 */
TEST_F(NodeTest, TestInteractionNode)
{
    auto *interaction_node = new sesstype::InteractionNode();
    EXPECT_EQ(interaction_node->type(), ST_NODE_SENDRECV);
    EXPECT_EQ(interaction_node->msgsig()->label(), "");
    EXPECT_EQ(NULL, interaction_node->from()); // Defaults to NULL
    EXPECT_EQ(interaction_node->num_to(), 0);

    auto *from = new sesstype::Role("F");
    auto *to0 = new sesstype::Role("T");
    auto *to1 = new sesstype::Role("TT");
    auto *to2 = new sesstype::Role("TTT");

    interaction_node->add_to(to0);
    EXPECT_EQ(interaction_node->num_to(), 1);
    EXPECT_EQ(interaction_node->to(0), to0);

    interaction_node->add_to(to1);
    EXPECT_EQ(interaction_node->num_to(), 2);
    EXPECT_EQ(interaction_node->to(1), to1);

    interaction_node->add_to(to2);
    EXPECT_EQ(interaction_node->num_to(), 3);
    EXPECT_EQ(interaction_node->to(2), to2);

    interaction_node->set_from(from);
    EXPECT_EQ(interaction_node->from(), from);

    auto *node2 = new sesstype::parameterised::InteractionNode();
    EXPECT_EQ(NULL, node2->cond()); // Defaults to NULL

    auto *cond = new sesstype::MsgCond("Alice");
    node2->set_cond(cond);
    EXPECT_EQ(node2->cond(), cond);
    delete interaction_node;
    delete node2;

    auto *msgsig = new sesstype::MsgSig("T");
    auto *interaction_node_with_msg = new sesstype::InteractionNode(msgsig);
    delete interaction_node_with_msg;
}

/**
 * \test RecurNode operations.
 */
TEST_F(NodeTest, TestRecurNode)
{
    auto *node = new sesstype::RecurNode("label");
    EXPECT_EQ(node->type(), ST_NODE_RECUR);
    EXPECT_EQ(node->label(), "label");
    node->set_label("new label");
    EXPECT_EQ(node->label(), "new_label");
    EXPECT_EQ(node->num_child(), 0);
    delete node;
}

/**
 * \test ContinueNode operations.
 */
TEST_F(NodeTest, TestContinueNode)
{
    auto *node = new sesstype::ContinueNode("label");
    EXPECT_EQ(node->type(), ST_NODE_CONTINUE);
    EXPECT_EQ(node->label(), "label");
    node->set_label("new label");
    EXPECT_EQ(node->label(), "new_label");
    delete node;
}

/**
 * \test ChoiceNode operations.
 */
TEST_F(NodeTest, TestChoiceNode)
{
    auto *role = new Role("Choice");
    auto *node = new sesstype::ChoiceNode();
    EXPECT_EQ(node->type(), ST_NODE_CHOICE);
    node->set_atrole(role);
    EXPECT_EQ(node->at(), role);
    EXPECT_EQ(node->num_child(), 0);
    delete node;

    auto *role2 = new Role("Choice2");
    auto *node2 = new sesstype::ChoiceNode(role2);
    EXPECT_EQ(node2->type(), ST_NODE_CHOICE);
    EXPECT_EQ(node2->at(), role2);
    EXPECT_EQ(node2->num_child(), 0);
    delete node2;
}

/**
 * \test ForNode operations.
 */
TEST_F(NodeTest, TestForNode)
{
    auto *rng = new sesstype::parameterised::RngExpr("i",
            new sesstype::parameterised::ValExpr(1),
            new sesstype::parameterised::VarExpr("N"));
    auto *node = new sesstype::parameterised::ForNode(rng);
    EXPECT_EQ(node->type(), ST_NODE_FOR);
    EXPECT_EQ(node->bind_expr(), rng);
    EXPECT_EQ(node->num_child(), 0);
    delete node;
}

/**
 * \test AllReduceNode operations.
 */
TEST_F(NodeTest, TestAllReduceNode)
{
    auto *node = new sesstype::parameterised::AllReduceNode();
    EXPECT_EQ(node->type(), ST_NODE_ALLREDUCE);
    auto *msgsig2 = new sesstype::MsgSig("___");
    node->set_msgsig(msgsig2);
    EXPECT_EQ(node->msgsig(), msgsig2);
    delete node;

    auto *msgsig = new sesstype::MsgSig("_");
    auto *node_withsig = new sesstype::parameterised::AllReduceNode(msgsig);
    EXPECT_EQ(node_withsig->type(), ST_NODE_ALLREDUCE);
    EXPECT_EQ(node_withsig->msgsig(), msgsig);

    delete node_withsig;
}

/**
 * \test OneofNode operations.
 */
TEST_F(NodeTest, TestOneofNode)
{
    auto *role = new sesstype::parameterised::Role("R");
    role->add_param(new sesstype::parameterised::RngExpr(
                new sesstype::parameterised::ValExpr(2),
                new sesstype::parameterised::ValExpr(10)));
    auto *role2 = new sesstype::parameterised::Role("R2");
    role2->add_param(new sesstype::parameterised::RngExpr(
                new sesstype::parameterised::ValExpr(2),
                new sesstype::parameterised::ValExpr(10)));
    auto *node = new sesstype::parameterised::OneofNode(role, 0);
    EXPECT_EQ(node->type(), ST_NODE_ONEOF);
    EXPECT_EQ(node->unordered(), false);
    EXPECT_EQ(node->selector_role(), role);
    EXPECT_EQ(node->selector_role_dimen(), 0);
    node->set_selector_role(role2, 0);
    node->set_unordered(true);
    EXPECT_EQ(node->unordered(), true);
    delete node;
}

/**
 * \test IfNode operations.
 */
TEST_F(NodeTest, TestIfNode)
{
    auto *cond = new sesstype::MsgCond("COND");
    auto *node = new sesstype::parameterised::IfNode(cond);
    EXPECT_EQ(node->type(), ST_NODE_IF);
    EXPECT_EQ(node->cond(), cond);
    delete node;
}

/**
 * \test Basic construction and use of Node.
 */
TEST_F(NodeTest, BasicUsage)
{
    auto *msgsig = new sesstype::MsgSig("L");
    auto *interaction_node = new sesstype::InteractionNode(msgsig);
    EXPECT_EQ(interaction_node->msgsig(), msgsig);
    EXPECT_EQ(interaction_node->type(), ST_NODE_SENDRECV);
    interaction_node->set_from(new Role("Alice"));
    interaction_node->add_to(new Role("Bob"));
    interaction_node->add_to(new Role("Carol"));

    auto *block_node = new sesstype::BlockNode();
    EXPECT_EQ(block_node->type(), ST_NODE_ROOT);
    EXPECT_EQ(block_node->num_child(), 0);
    block_node->append_child(interaction_node);
    EXPECT_EQ(block_node->num_child(), 1);
    auto *block_node2 = new sesstype::BlockNode();
    block_node->append_child(block_node2);
    EXPECT_EQ(block_node->num_child(), 2);
    EXPECT_EQ(block_node->child(0)->type(), ST_NODE_SENDRECV);
    EXPECT_EQ(block_node->child(1)->type(), ST_NODE_ROOT);
    EXPECT_EQ(block_node->child(1)->type(), block_node2->type());

    auto *recur_node = new sesstype::RecurNode("rec"+0);
    EXPECT_EQ(recur_node->num_child(), 0);
    EXPECT_EQ(recur_node->type(), ST_NODE_RECUR);
    block_node->append_child(recur_node);
    EXPECT_EQ(block_node->num_child(), 3);
    auto *choice_node = new sesstype::ChoiceNode();
    choice_node->set_atrole(new Role("Alice"));
    EXPECT_EQ(choice_node->at()->name(), "Alice");
    recur_node->append_child(choice_node);
    EXPECT_EQ(recur_node->num_child(), 1);
    EXPECT_EQ(recur_node->child(0), choice_node);
    recur_node->append_child(new sesstype::ContinueNode("rec"+0));

    delete block_node;
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
