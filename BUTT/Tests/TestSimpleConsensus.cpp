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
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 3", testSearchNodes3());
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 4", testSearchNodes4());
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 5", testSearchNodes5());
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 6", testSearchNodes6());
    BUTT_RUN_TEST("TestSimpleConsensus testSearchNodes 7", testSearchNodes7());
    BUTT_POST_TESTS();
}

/**
 * Tests that no consensus at all returns empty taxonomy string.
 *
 * Input:    (("K#a")
 *            ("K#x"))
 *
 * Expected: "K#;P#;C#;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes1()
{
    return false;
}

/**
 * Tests consensus of perfect hit.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_1", "P#b_1", "C#c_1"))
 *
 * Expected: "K#a_1;P#b_1;C#c_1;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes2()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_1", "P#b_1", "C#c_1"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c_1;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of hit down to C-level: first word OK, second word bad.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_1", "P#b_1", "C#c_2"))
 *
 * Expected: "K#a_1;P#b_1;C#c;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes3()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_1", "P#b_1", "C#c_2"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of hit down to P-level: first word OK, second word OK.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_1", "P#b_1", "C#x_2"))
 *
 * Expected: "K#a_1;P#b_1;C#;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes4()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_1", "P#b_1", "C#x_2"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of hit down to P-level: first word OK, second word bad.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_1", "P#b_2", "C#x_2"))
 *
 * Expected: "K#a_1;P#b;C#;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes5()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_1", "P#b_2", "C#x_2"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a_1;P#b;C#;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of hit down to K-level, first word OK, second word OK.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_1", "P#x_2", "C#x_2"))
 *
 * Expected: "K#a_1;P#;C#;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes6()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_1", "P#x_2", "C#x_2"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a_1;P#;C#;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

/**
 * Tests consensus of hit down to K-level, first word OK, second word bad.
 *
 * Input:    (("K#a_1", "P#b_1", "C#c_1"),
 *            ("K#a_2", "P#x_2", "C#x_2"))
 *
 * Expected: "K#a;P#;C#;O#;F#;G#;S#"
 */
bool TestSimpleConsensus::testSearchNodes7()
{
    SimpleTaxConsensus consensus_builder;

    vector< vector< string> > tax_table = {
        {"K#a_1", "P#b_1", "C#c_1"},
        {"K#a_2", "P#x_2", "C#x_2"}
    };

    cerr<<consensus_builder.buildConsensus(tax_table)<<endl;

    BUTT_ASSERT_EQUALS("K#a;P#;C#;O#;F#;G#;S#", consensus_builder.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}
