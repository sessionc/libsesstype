/**
 * \file test/projection.cc
 * \brief Tests for sesstype::utils::Projection.
 */

#include "gtest/gtest.h"

#include <string>

#include "sesstype/role.h"
#include "sesstype/util.h"

#include "sesstype/node.h"
#include "sesstype/node/interaction.h"
#include "sesstype/node/recur.h"
#include "sesstype/node/continue.h"

namespace sesstype {
namespace tests {

class ProjectionTest : public ::testing::Test {
  protected:
    ProjectionTest() {}
};

/**
 * \test Basic usage of Role.
 */
TEST_F(ProjectionTest, BasicProjection)
{
    auto *root = new BlockNode();

    // Interaction 1.
    auto *ALICE = new Role("Alice");
    auto *BOB   = new Role("Bob");
    auto *CAROL = new Role("Carol");

    // ALICE --First()--> BOB, CAROL
    auto *interact_node = new InteractionNode(new MsgSig("First"));
    interact_node->set_sndr(ALICE);
    interact_node->add_rcvr(BOB);
    interact_node->add_rcvr(CAROL);
    root->append_child(interact_node);

    // Interaction 2.
    // ALICE --Second()--> CAROL
    auto *interact2_node = new InteractionNode(new MsgSig("Second"));
    interact2_node->set_sndr(ALICE);
    interact2_node->add_rcvr(CAROL);
    root->append_child(interact2_node);

    // Recur 1.
    auto *recur1_node = new RecurNode("Rec0");
    root->append_child(recur1_node);

    // Recur 2.
    auto *recur2_node = new RecurNode("Rec1");
    recur1_node->append_child(recur2_node);

    // Interaction 3.
    // ALICE --Label()--> MALLORY
    auto *MALLORY = new Role("Mallory");
    auto *msgsig1 = new MsgSig("Label");
    auto *interact3_node = new InteractionNode();
    interact3_node->set_sndr(ALICE);
    interact3_node->add_rcvr(MALLORY);
    interact3_node->set_msg(msgsig1);
    recur2_node->append_child(interact3_node);

    // Continue 1.
    auto *cont1_node = new ContinueNode("Rec0");
    recur1_node->append_child(cont1_node);

    // Interaction 4.
    // BOB --Third()--> MALLORY, ALICE
    auto *interact4_node = new InteractionNode(new MsgSig("Third"));
    interact4_node->set_sndr(BOB);
    interact4_node->add_rcvr(MALLORY);
    interact4_node->add_rcvr(ALICE);

    root->append_child(interact4_node);

    util::ProjectionVisitor project_wrt_bob(BOB);
    root->accept(project_wrt_bob);

    auto *endpoint_bob = project_wrt_bob.get_root();

    EXPECT_EQ(endpoint_bob->type(), ST_NODE_ROOT);
    auto *ep_bob_root = dynamic_cast<BlockNode *>(endpoint_bob);
    EXPECT_EQ(ep_bob_root->num_children(), 3);

    EXPECT_EQ(ep_bob_root->child(0)->type(), ST_NODE_SENDRECV);
    auto *ep_bob_interact0 = dynamic_cast<InteractionNode *>(ep_bob_root->child(0));
    EXPECT_EQ(ep_bob_interact0->msg()->label(), "First");
    EXPECT_EQ(ep_bob_interact0->sndr()->name(), "Alice");

    EXPECT_EQ(ep_bob_root->child(1)->type(), ST_NODE_RECUR);
    auto *ep_bob_recur0 = dynamic_cast<RecurNode *>(ep_bob_root->child(1));
    EXPECT_EQ(ep_bob_recur0->label(), "Rec0");
    EXPECT_EQ(ep_bob_recur0->num_children(), 2);

    EXPECT_EQ(ep_bob_recur0->child(0)->type(), ST_NODE_RECUR);
    auto *ep_bob_recur1 = dynamic_cast<RecurNode *>(ep_bob_recur0->child(0));
    EXPECT_EQ(ep_bob_recur1->label(), "Rec1");
    EXPECT_EQ(ep_bob_recur1->num_children(), 0);

    EXPECT_EQ(ep_bob_recur0->child(1)->type(), ST_NODE_CONTINUE);
    auto *ep_bob_interact1 = dynamic_cast<ContinueNode *>(ep_bob_recur0->child(1));
    EXPECT_EQ(ep_bob_interact1->label(), "Rec0");

    EXPECT_EQ(ep_bob_root->child(2)->type(), ST_NODE_SENDRECV);
    auto *ep_bob_interact2 = dynamic_cast<InteractionNode *>(ep_bob_root->child(2));
    EXPECT_EQ(ep_bob_interact2->msg()->label(), "Third");
    EXPECT_EQ(ep_bob_interact2->rcvr()->name(), "Mallory");
}

} // namespace tests
} // namespace sesstype

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
