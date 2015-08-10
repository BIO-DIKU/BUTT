#ifndef TESTSIMPLECONSENSUS_H
#define TESTSIMPLECONSENSUS_H

#include "TestHelper.h"
#include "Search/SimpleTaxConsensus.h"

class TestSimpleTaxConsensus
{
private:
    SimpleTaxConsensus consensus;

public:
    TestSimpleTaxConsensus();

    bool runTests();

    /**
     * Tests that no consensus at all returns empty taxonomy string.
     *
     * Input:    (("K#a")
     *            ("K#x"))
     *
     * Expected: "K#;P#;C#;O#;F#;G#;S#"
     */
    bool testBuildConsensus1();

    /**
     * Tests consensus of perfect hit.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "1", "P#b", "1", "C#c", "1"))
     *
     * Expected: "K#a_1;P#b_1;C#c_1;O#;F#;G#;S#"
     */
    bool testBuildConsensus2();

    /**
     * Tests consensus of hit down to C-level: first word OK, second word bad.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "1", "P#b", "1", "C#c", "2"))
     *
     * Expected: "K#a_1;P#b_1;C#c;O#;F#;G#;S#"
     */
    bool testBuildConsensus3();

    /**
     * Tests consensus of hit down to P-level: first word OK, second word OK.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "1", "P#b", "1", "C#x", "2"))
     *
     * Expected: "K#a_1;P#b_1;C#;O#;F#;G#;S#"
     */
    bool testBuildConsensus4();

    /**
     * Tests consensus of hit down to P-level: first word OK, second word bad.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "1", "P#b", "2", "C#x", "2"))
     *
     * Expected: "K#a_1;P#b;C#;O#;F#;G#;S#"
     */
    bool testBuildConsensus5();

    /**
     * Tests consensus of hit down to K-level, first word OK, second word OK.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "1", "P#x", "2", "C#x", "2"))
     *
     * Expected: "K#a_1;P#;C#;O#;F#;G#;S#"
     */
    bool testBuildConsensus6();

    /**
     * Tests consensus of hit down to K-level, first word OK, second word bad.
     *
     * Input:    (("K#a", "1", "P#b", "1", "C#c", "1"),
     *            ("K#a", "2", "P#x", "2", "C#x", "2"))
     *
     * Expected: "K#a;P#;C#;O#;F#;G#;S#"
     */
    bool testBuildConsensus7();
};

#endif // TESTSIMPLECONSENSUS_H
