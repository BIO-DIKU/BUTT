#include "TestTaxBuilder.h"

#include <iostream>

#include "TaxBuilder.h"
#include "SeqToKMers.h"
#include "TestHelper.h"

TestTaxBuilder::TestTaxBuilder():
    builder(SeqToKMers(3,1))
{

}

bool TestTaxBuilder::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestTaxBuilder test 1", test1());
    //BUTT_RUN_TEST("TestTaxBuilder test 2", test2());
    //BUTT_RUN_TEST("TestTaxBuilder test 3", test3());
    //BUTT_RUN_TEST("TestTaxBuilder test 4", test4());
    //BUTT_RUN_TEST("TestTaxBuilder test 5", test5());
    //BUTT_RUN_TEST("TestTaxBuilder test 6", test6());
    //BUTT_RUN_TEST("TestTaxBuilder test 7", test7());
    //BUTT_RUN_TEST("TestTaxBuilder test 8", test8());
    //BUTT_RUN_TEST("TestTaxBuilder test 9", test9());
    //BUTT_RUN_TEST("TestTaxBuilder test 10", test10());
    BUTT_POST_TESTS();

}

bool TestTaxBuilder::test1()
{
    builder.addTaxEntry("K#B;P#E", "AAGA");

    BUTT_ASSERT_EQUALS(0, builder.treeSize(), "Bad treeSize. Expected 0, was "+std::to_string(builder.treeSize()));
    BUTT_ASSERT_EQUALS("root", builder.getNode(0).getName(), "Root name mismatch");
    BUTT_ASSERT_EQUALS("B", builder.getNode(1).getName(), "Kingdom name mismatch");
    BUTT_ASSERT_EQUALS("E", builder.getNode(2).getName(), "Phylum name mismatch");
    BUTT_ASSERT_EQUALS(3, builder.treeSize(), "Bad treeSize. Expected 3, was "+std::to_string(builder.treeSize()));

    BUTT_ASSERT_EQUALS(0, builder.getNode(1).getParent().node_id, "Node 0 should be parent of 1");
    BUTT_ASSERT_EQUALS(1, builder.getNode(2).getParent().node_id, "Node 1 should be parent of 2");
}

