#ifndef TESTTAXSEARCH_H
#define TESTTAXSEARCH_H

/**
 * @brief The TestTaxSearch class
 * The following tree-layout is used for all tests
 *               I
 *            /     \
 *          G         H
 *       /  |  \
 *     D    E    F
 *        / | \
 *       A  B  C
 */
class TestTaxSearch
{
public:
    TestTaxSearch();

    bool testTaxSearch();

    bool testSearch();

private:
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
};

#endif // TESTTAXSEARCH_H
