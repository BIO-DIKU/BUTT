/* Copyright 2015 BIO-DIKU */

#ifndef BUTT_TESTS_TESTTAXSEARCH_H_
#define BUTT_TESTS_TESTTAXSEARCH_H_

/**
 * @brief The TestTaxSearch class
 */
class TestTaxSearch {
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
     *               i
     *            /
     *          g
     *       /  |  \
     *     d    e    f
     *        / | \
     *       a  b  c
     */
    
    /**
     * Test that more than one hit can be returned
     * hits_max = 2
     * best_only = false
     * Query hits only: a, b, e, g, i
     * Expected: {a,b}
     */
    bool test1();

    /**
     * Test that only hits_max are returned
     * hits_max = 2
     * best_only = false
     * Query hits only: a, b, c, e, g, i
     * hits(a)>hits(b)>hits(c)
     * Expected: {a,b}
     */
    bool test2();

    /**
     * Tests that hits are sorted (together with test2)
     * hits_max = 2
     * best_only = false
     * Query hits only: a, b, c, e, g, i
     * hits(b)>hits(a)>hits(c)
     * Expected: {b,a}
     */
    bool test3();

    /**
     * Tests best_only
     * hits_max = 2
     * best_only = true
     * Query hits only: a, b, c, e, g, i
     * hits(a)>hits(b)>hits(c)
     * Expected: {a}
     */
    bool test4();

    /**
     * Tests best_only with more than one hit
     * hits_max = 2
     * best_only = true
     * Query hits only: a, b, c, e, g, i
     * hits(a)=hits(b)>hits(c)
     * Expected: {a,b}
     */
    bool test5();

    /**
     * Tests best_only when there are more than hits_max hits
     * hits_max = 2
     * best_only = true
     * Query hits only: a, b, c, e, g, i
     * hits(a)=hits(b)=hits(c)
     * Expected: {a,b}|{a,c}|{b,c}
     */
    bool test6();

    /**
     * Tests hits_max > hits return OK. 
     * hits_max = 5
     * best_only = true
     * Query hits only: a, b, c, e, g, i
     * hits(a)=hits(b)=hits(c)
     * Expected: 3 hits
     */
    bool test7();

    /**
     * Tests hits on second level
     * hits_max = 2
     * best_only = false
     * Query hits only: e, g, i
     * Expected: {e}
     */
    bool test8();

    /**
     * Tests that empty set is returned if no hits
     * hits_max = 2
     * best_only = false
     * Query hits only: {}
     * Expected: {}  / "Unclassified"
     */
    bool test9();

    /*
     * Test-cases for testSearch.
     *
     * The following tree-layout is used for testSearchNodes1-8:
     *                 r
     *    		       |
     *         a_1  a_1  a_2  z_7
     *               |
     *         b_1  b_1  b_2  y_8
     *               |
     *         c_1  c_1  c_2  x_9
     *
     */

    /**
     * Tests that empty search for non-existing taxonomy gives consensus
     * taxonomy with all levels empty.
     * Input: Kmers not corresponding to any node
     * Expected: ("query_name", "K#;P#;C#;O#;F#;G#;S#", 0)
     */
    bool testSearchNodes1();

    /**
     * Tests consensus of perfect hit
     * Input: kmers matching: c_1, c_1
     * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#c_1(100/100);O#;F#;G#;S#", 2)
     */
    bool testSearchNodes2();

    /**
     * Tests consensus of hit down to C-level, first word
     * Input: kmers matching: c_1, c_2
     * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#C(100);O#;F#;G#;S#", 2)
     */
    bool testSearchNodes3();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: c_1, x_9
     * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes4();

    /**
     * Tests consensus of hit down to P-level, second word
     * Input: kmers matching: b_1, b_1
     * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes5();

    /**
     * Tests consensus of hit down to P-level, first word
     * Input: kmers matching: b_1, b_2
     * Expected: ("query_name", "K#a_1(100/100);P#B(100);C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes6();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: b_1, y_8
     * Expected: ("query_name", "K#a_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes7();

    /**
     * Tests consensus of hit down to K-level, second word
     * Input: kmers matching: a_1, a_1
     * Expected: ("query_name", "K#a_1(100/100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes8();

    /**
     * Tests consensus of hit down to K-level, first word
     * Input: kmers matching: a_1, a_2
     * Expected: ("query_name", "K#A(100);P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes9();

    /**
     * Tests no consensus, but with hits
     * Input: kmers matching: a_1, z_7
     * Expected: ("query_name", "K#;P#;C#;O#;F#;G#;S#", 2)
     */
    bool testSearchNodes10();
};

#endif   // BUTT_TESTS_TESTTAXSEARCH_H_
