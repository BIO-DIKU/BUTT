#include "TestSimpleConsensus.h"

#include "Search/SimpleTaxConsensus.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

TestSimpleConsensus::TestSimpleConsensus()
{
}

bool TestSimpleConsensus::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 1", testSearchNodes1());
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 2", testSearchNodes2());
    BUTT_POST_TESTS();
}


/*
 * TestSimpleTaxConsensus::test-cases for testSearch.
 * The following tree-layout is used for test1-test8
 *                 r
 *    		       |
 *         A_1  A_1  A_2  Z_7
 *               |
 *         B_1  B_1  B_2  Y_8
 *               |
 *      C_1  C_1  C_2  X_9
 *
 */

/**
 * Tests that empty search for non-existing taxonomy gives consensus
 * taxonomy with all levels empty.
 * Input: Kmers not corresponding to any node
 * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 0)
 */
bool TestSimpleConsensus::testSearchNodes1()
{

    return false;
}

/**
 * Tests consensus of perfect hit
 * Input: kmers matching: C_1, C_1
 * Expected: ("Q", "K#A_1;P#B_1;C#C_1;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes2()
{

    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#A_1","P#B_1","C#C_1"},
        {"K#A_1","P#B_1","C#C_1"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;
    BUTT_ASSERT_EQUALS("K#A_1;P#B_1;C#C_1", consensus_builder.buildConsensus(tax_table), "Perfect match didnt work");

    return true;
}

/**
 * Tests consensus of hit down to C-level, first word
 * Input: kmers matching: C_1, C_2
 * Expected: ("Q", "K#A_1;P#B_1;C#C;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes3()
{

}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: C_1, X_9
 * Expected: ("Q", "K#A_1;P#B_1;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes4()
{

}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: B_1, B_1
 * Expected: ("Q", "K#A_1;P#B_1;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes5()
{

}

/**
 * Tests consensus of hit down to P-level, first word
 * Input: kmers matching: B_1, B_2
 * Expected: ("Q", "K#A_1;P#B;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes6()
{

}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: B_1, Y_8
 * Expected: ("Q", "K#A_1;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes7()
{

}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: A_1, A_1
 * Expected: ("Q", "K#A_1;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes8()
{

}

/**
 * Tests consensus of hit down to K-level, first word
 * Input: kmers matching: A_1, A_2
 * Expected: ("Q", "K#A;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes9()
{

}

/**
 * Tests no consensus, but with hits
 * Input: kmers matching: A_1, Z_7
 * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestSimpleConsensus::testSearchNodes10()
{

}
