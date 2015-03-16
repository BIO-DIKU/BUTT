#include "TestTaxSearch.h"

#include "TestHelper.h"
#include "Search/TaxSearch.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

TestTaxSearch::TestTaxSearch()
{
}

bool TestTaxSearch::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestTaxSearch test 1", test1());
    BUTT_RUN_TEST("TestTaxSearch test 2", test2());
    BUTT_RUN_TEST("TestTaxSearch test 3", test3());
    BUTT_RUN_TEST("TestTaxSearch test 4", test4());
    BUTT_RUN_TEST("TestTaxSearch test 5", test5());
    BUTT_RUN_TEST("TestTaxSearch test 6", test6());
    BUTT_RUN_TEST("TestTaxSearch test 7", test7());
    BUTT_RUN_TEST("TestTaxSearch test 8", test8());
    BUTT_POST_TESTS();

}


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
bool TestTaxSearch::test1()
{
    //"#NODE_ID	PARENT_ID	LEVEL	NAME"
    string taxIndexContents = "";
    taxIndexContents += "0\t-1\t0\tI\n";
    taxIndexContents += "1\t0\t1\tG\n";
    taxIndexContents += "2\t1\t2\tD\n";
    taxIndexContents += "3\t1\t2\tF\n";
    taxIndexContents += "4\t1\t2\tE\n";
    taxIndexContents += "5\t4\t3\tA\n";
    taxIndexContents += "6\t4\t3\tB\n";
    taxIndexContents += "7\t4\t3\tC\n";

    ofstream output("temp_taxIndex.txt");
    output<<taxIndexContents;
    output.close();

    //"#LEVEL	KMER	NODES"
    string kmerIndexContents = "";
    kmerIndexContents += "0\t0\t0\n";
    kmerIndexContents += "1\t0\t1\n";
    kmerIndexContents += "2\t0\t4\n";
    kmerIndexContents += "3\t0\t5;6\n";

    output = ofstream("temp_kmerIndex.txt");
    output<<kmerIndexContents;
    output.close();

    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0);
    string file1("temp_taxIndex.txt"); searcher.readTaxIndex(file1);
    string file2("temp_kmerIndex.txt"); searcher.readKMerIndex(file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    Hit h = searcher.search("seqname", "AAAA");
    BUTT_ASSERT_EQUALS("seqname", get<0>(h), "Sequence name should be seqname but is "+get<0>(h));
    BUTT_ASSERT_EQUALS("I;G;E", get<1>(h), "Consensus should be I;G;E but is "+get<1>(h));
    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 nodes");

    return true;

}


/**
 * Test that only hits_max are returned
 * hits_max = 2
 * best_only = false
 * Query hits only: A, B, C, E, G, I
 * hits(A)>hits(B)>hits(C)
 * Expected: {A,B}
 */
bool TestTaxSearch::test2()
{

}

/**
 * Tests that hits are sorted (together with test2)
 * hits_max = 2
 * best_only = false
 * Query hits only: A, B, C, E, G, I
 * hits(B)>hits(A)>hits(C)
 * Expected: {B,A}
 */
bool TestTaxSearch::test3(){

}

/**
 * Tests best_only
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(A)>hits(B)>hits(C)
 * Expected: {A}
 */
bool TestTaxSearch::test4()
{

}

/**
 * Tests best_only with more than one hit
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(A)=hits(B)>hits(C)
 * Expected: {A,B}
 */
bool TestTaxSearch::test5()
{

}

/**
 * Tests best_only when there are more than hits_max hits
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(A)=hits(B)=hits(C)
 * Expected: {A,B}|{A,C}|{B,C}
 */
bool TestTaxSearch::test6()
{

}

/**
 * Tests hits on second level
 * hits_max = 2
 * best_only = false
 * Query hits only: E, G, I
 * Expected: {E}
 */
bool TestTaxSearch::test7()
{

}

/**
 * Tests that empty set is returned if no hits
 * hits_max = 2
 * best_only = false
 * Query hits only: {}
 * Expected: {}
 */
bool TestTaxSearch::test8()
{

}



/*
 * TestTaxSearch::test-cases for testSearch.
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
bool TestTaxSearch::testSearchNodes1()
{

}

/**
 * Tests consensus of perfect hit
 * Input: kmers matching: C_1, C_1
 * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C_1(100/100);O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes2()
{

}

/**
 * Tests consensus of hit down to C-level, first word
 * Input: kmers matching: C_1, C_2
 * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#C(100);O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes3()
{

}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: C_1, X_9
 * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes4()
{

}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: B_1, B_1
 * Expected: ("Q", "K#A_1(100/100);P#B_1(100/100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes5()
{

}

/**
 * Tests consensus of hit down to P-level, first word
 * Input: kmers matching: B_1, B_2
 * Expected: ("Q", "K#A_1(100/100);P#B(100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes6()
{

}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: B_1, Y_8
 * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes7()
{

}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: A_1, A_1
 * Expected: ("Q", "K#A_1(100/100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes8()
{

}

/**
 * Tests consensus of hit down to K-level, first word
 * Input: kmers matching: A_1, A_2
 * Expected: ("Q", "K#A(100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes9()
{

}

/**
 * Tests no consensus, but with hits
 * Input: kmers matching: A_1, Z_7
 * Expected: ("Q", "K#;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes10()
{

}
