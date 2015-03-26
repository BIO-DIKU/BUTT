#include "TestAll.h"

#include "TestFasta.h"
#include "TestSeqToKMers.h"
#include "TestTaxBuilder.h"
#include "TestSimpleConsensus.h"
#include "TestTaxSearch.h"
#include "TestHelper.h"

#include <iostream>

TestAll::TestAll()
{
}

bool TestAll::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestAll: TestFasta", TestFasta("../BUTT/Tests/Fastas").runTests());
    BUTT_RUN_TEST("TestAll: TestSeqToKMers", TestSeqToKMers().runTests());
    BUTT_RUN_TEST("TestAll: TestTaxBuilder", TestTaxBuilder().runTests());
    BUTT_RUN_TEST("TestAll: TestSimpleConsensus", TestSimpleConsensus().runTests());
    BUTT_RUN_TEST("TestAll: TestTaxSearch", TestTaxSearch().runTests());
    BUTT_POST_TESTS();
}
