/* Copyright 2015 BIO-DIKU */

#include "TestAll.h"
#include "TestFasta.h"
#include "TestSeqToKMers.h"
#include "TestTaxBuilder.h"
#include "TestSimpleTaxConsensus.h"
#include "TestCleverTaxConsensus.h"
#include "TestTaxSearch.h"
#include "TestHelper.h"

#include <iostream>

TestAll::TestAll() {
}

bool TestAll::runTests() {
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestAll: TestFasta", TestFasta("../BUTT/Tests/Fastas").
        runTests());
    BUTT_RUN_TEST("TestAll: TestSeqToKMers", TestSeqToKMers().runTests());
    BUTT_RUN_TEST("TestAll: TestTaxBuilder", TestTaxBuilder().runTests());
    BUTT_RUN_TEST("TestAll: TestSimpleTaxConsensus", TestSimpleTaxConsensus().
        runTests());
    BUTT_RUN_TEST("TestAll: TestCleverTaxConsensus", TestCleverTaxConsensus().
        runTests());
    BUTT_RUN_TEST("TestAll: TestTaxSearch", TestTaxSearch().runTests());
    BUTT_POST_TESTS();
}
