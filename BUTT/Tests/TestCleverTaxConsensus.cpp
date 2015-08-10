/* Copyright 2015 BIO-DIKU */

#include "TestHelper.h"
#include "TestCleverTaxConsensus.h"
#include "Search/TaxConsensus.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

TestCleverTaxConsensus::TestCleverTaxConsensus(): consensus({"K", "P", "C", "O", "F", "G", "S"}) {}

bool TestCleverTaxConsensus::runTests() {
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 1",  testBuildConsensus1());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 2",  testBuildConsensus2());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 3",  testBuildConsensus3());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 4",  testBuildConsensus4());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 5",  testBuildConsensus5());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 6",  testBuildConsensus6());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 7",  testBuildConsensus7());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 8",  testBuildConsensus8());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 9",  testBuildConsensus9());
    BUTT_RUN_TEST("TestCleverTaxConsensus testBuildConsensus 10", testBuildConsensus10());
    BUTT_POST_TESTS();
}

/**
 * Tests that empty search for non-existing taxonomy gives consensus
 * taxonomy with all levels empty.
 * Input: Kmers not corresponding to any node
 * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 0)
 */
bool TestCleverTaxConsensus::testBuildConsensus1() {
    vector< vector< string> > tax_table = {
        {"K#a"},
        {"K#x"}
    };

    BUTT_ASSERT_EQUALS("K#;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of perfect hit
 * Input: kmers matching: C_1, C_1
 * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C_1(100/100);O#;F#;G#;S#", 2)
 */
bool TestCleverTaxConsensus::testBuildConsensus2() {
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#c", "1"}
    };

    BUTT_ASSERT_EQUALS("K#A_1(100/100);P#B_1(100/100);C#C_1(100/100);O#;F#;G#;S#",
                       consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestCleverTaxConsensus::testBuildConsensus3() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus4() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus5() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus6() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus7() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus8() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus9() {
    return false;
}

bool TestCleverTaxConsensus::testBuildConsensus10() {
    return false;
}

