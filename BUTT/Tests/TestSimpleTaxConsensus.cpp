#include "TestSimpleTaxConsensus.h"
#include "Search/SimpleTaxConsensus.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

TestSimpleTaxConsensus::TestSimpleTaxConsensus(): consensus({"K", "P", "C", "O", "F", "G", "S"})
{

}

bool TestSimpleTaxConsensus::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 1", testBuildConsensus1());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 2", testBuildConsensus2());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 3", testBuildConsensus3());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 4", testBuildConsensus4());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 5", testBuildConsensus5());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 6", testBuildConsensus6());
    BUTT_RUN_TEST("TestSimpleTaxConsensus testBuildConsensus 7", testBuildConsensus7());
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
bool TestSimpleTaxConsensus::testBuildConsensus1()
{
    vector< vector< string> > tax_table = {
        {"K#a"},
        {"K#x"}
    };

    BUTT_ASSERT_EQUALS("K#;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus2()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#c", "1"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c_1;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus3()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#c", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#c;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus4()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "1", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b_1;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus5()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#b", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#b;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus6()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "1", "P#x", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a_1;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}

bool TestSimpleTaxConsensus::testBuildConsensus7()
{
    vector< vector< string> > tax_table = {
        {"K#a", "1", "P#b", "1", "C#c", "1"},
        {"K#a", "2", "P#x", "2", "C#x", "2"}
    };

    BUTT_ASSERT_EQUALS("K#a;P#;C#;O#;F#;G#;S#", consensus.buildConsensus(tax_table), "Perfect match didn't work.");

    return true;
}
