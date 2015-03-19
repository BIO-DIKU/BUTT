#ifndef TESTCLEVERTAXCONSENSUS_H
#define TESTCLEVERTAXCONSENSUS_H

class TestCleverTaxConsensus
{
public:
    TestCleverTaxConsensus();

    /**
     * Tests that empty search for non-existing taxonomy gives consensus
     * taxonomy with all levels empty.
     * Input: Kmers not corresponding to any node
     * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 0)
     */
    bool testSearchNodes1();

    /**
     * Tests consensus of perfect hit
     * Input: kmers matching: C_1, C_1
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C_1(100/100);O#;F#;G#;S#", 2)
     */
    bool testSearchNodes2();

    /**
     * Tests consensus of hit down to C-level, first word
     * Input: kmers matching: C_1, C_2
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C(100);O#;F#;G#;S#", 2)
     */
    bool testSearchNodes3();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: C_1, X_9
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes4();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: B_1, B_1
     * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes5();

    /**
     * Tests consensus of hit down to P-level, first word
     * Input: kmers matching: B_1, B_2
     * Expected: ("Q", "K#A_1(100/100);P#B(100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes6();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: B_1, Y_8
     * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes7();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: A_1, A_1
     * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes8();

    /**
     * Tests consensus of hit down to K-level, first word
     * Input: kmers matching: A_1, A_2
     * Expected: ("Q", "K#A(100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes9();

    /**
     * Tests no consensus, but with hits
     * Input: kmers matching: A_1, Z_7
     * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes10();

};

#endif // TESTCLEVERTAXCONSENSUS_H
