/* Copyright 2015 BIO-DIKU */

#ifndef BUTT_TESTS_TESTCLEVERTAXCONSENSUS_H_
#define BUTT_TESTS_TESTCLEVERTAXCONSENSUS_H_

#include "TestHelper.h"
#include "Search/TaxConsensus.h"
#include "Search/CleverTaxConsensus.h"

class TestCleverTaxConsensus {
 private:
    CleverTaxConsensus consensus;

 public:
    TestCleverTaxConsensus();

    bool runTests();

    /**
     * Tests that empty search for non-existing taxonomy gives consensus
     * taxonomy with all levels empty.
     * Input: Kmers not corresponding to any node
     * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 0)
     */
    bool testBuildConsensus1();

    /**
     * Tests consensus of perfect hit
     * Input: kmers matching: C_1, C_1
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C_1(100/100);O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus2();

    /**
     * Tests consensus of hit down to C-level, first word
     * Input: kmers matching: C_1, C_2
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C(100);O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus3();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: C_1, X_9
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus4();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: B_1, B_1
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus5();

    /**
     * Tests consensus of hit down to P-level, first word
     * Input: kmers matching: B_1, B_2
     * Expected: ("Q", "K#A_1(100/100);P#B(100);C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus6();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: B_1, Y_8
     * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus7();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: A_1, A_1
     * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus8();

    /**
     * Tests consensus of hit down to K-level, first word
     * Input: kmers matching: A_1, A_2
     * Expected: ("Q", "K#A(100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus9();

    /**
     * Tests no consensus, but with hits
     * Input: kmers matching: A_1, Z_7
     * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 2)
     */
    bool testBuildConsensus10();
};

#endif   // BUTT_TESTS_TESTCLEVERTAXCONSENSUS_H_
