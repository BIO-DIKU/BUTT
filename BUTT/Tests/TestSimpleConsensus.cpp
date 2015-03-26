#include "TestSimpleConsensus.h"
#include "Search/SimpleTaxConsensus.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

TestSimpleConsensus::TestSimpleConsensus(): consensus({"K", "P", "C", "O", "F", "G", "S"})
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
    vector< vector< string> > tax_table = {
        {"K#a"},
        {"K#x"}
    };

    BUTT_ASSERT_EQUALS("K#;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes2()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#c", "1"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c_1;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes3()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#c", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes4()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes5()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes6()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#x", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleConsensus::testSearchNodes7()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "2", "P#x", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}
