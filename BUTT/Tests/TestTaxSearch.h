#ifndef TESTTAXSEARCH_H
#define TESTTAXSEARCH_H

/**
 * @brief The TestTaxSearch class
 */
class TestTaxSearch
{
public:
    TestTaxSearch();

    bool runTests();
private:
    bool testTaxSearch();

    bool testSearchNodes();

    bool testSearch();

    /**
     * Test that TaxSearchException is thrown if either the kmer index file
     * or taxonomy index file does not exist.
     */
    bool testIOExceptions();

    /*
     * test-cases for testSearchNodes.
     * The following tree-layout is used for test1-test8
     *               I
     *            /
     *          G
     *       /  |  \
     *     D    E    F
     *        / | \
     *       A  B  C
     */
    /**
     * Test that more than one hit can be returned
     * hits_max = 2
     * best_only = false
     * Query hits only: A, B, E, G, I
     * Expected: {A,B}
     */
    bool test1();

    /**
     * Test that only hits_max are returned
     * hits_max = 2
     * best_only = false
     * Query hits only: A, B, C, E, G, I
     * hits(A)>hits(B)>hits(C)
     * Expected: {A,B}
     */
    bool test2();

    /**
     * Tests that hits are sorted (together with test2)
     * hits_max = 2
     * best_only = false
     * Query hits only: A, B, C, E, G, I
     * hits(B)>hits(A)>hits(C)
     * Expected: {B,A}
     */
    bool test3();

    /**
     * Tests best_only
     * hits_max = 2
     * best_only = true
     * Query hits only: A, B, C, E, G, I
     * hits(A)>hits(B)>hits(C)
     * Expected: {A}
     */
    bool test4();

    /**
     * Tests best_only with more than one hit
     * hits_max = 2
     * best_only = true
     * Query hits only: A, B, C, E, G, I
     * hits(A)=hits(B)>hits(C)
     * Expected: {A,B}
     */
    bool test5();

    /**
     * Tests best_only when there are more than hits_max hits
     * hits_max = 2
     * best_only = true
     * Query hits only: A, B, C, E, G, I
     * hits(A)=hits(B)=hits(C)
     * Expected: {A,B}|{A,C}|{B,C}
     */
    bool test6();

    /**
     * Tests hits on second level
     * hits_max = 2
     * best_only = false
     * Query hits only: E, G, I
     * Expected: {E}
     */
    bool test7();

    /**
     * Tests that empty set is returned if no hits
     * hits_max = 2
     * best_only = false
     * Query hits only: {}
     * Expected: {}
     */
    bool test8();



    /*
     * test-cases for testSearch.
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

#endif // TESTTAXSEARCH_H
