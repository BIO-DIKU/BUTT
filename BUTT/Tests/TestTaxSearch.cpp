#include "TestTaxSearch.h"

#include "TestHelper.h"
#include "Search/TaxSearch.h"
#include "Search/SimpleTaxConsensus.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

#define LEVEL_NAMES {"K", "P", "C", "O", "F", "G", "S"}

using namespace std;

TestTaxSearch::TestTaxSearch()
{

}

bool TestTaxSearch::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestTaxSearch test IO", testIOExceptions());
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

bool TestTaxSearch::testIOExceptions()
{
    try{
        string kmer_index_path("randomNonexistingASDFpath.txt1");
        string tax_index_path("temp_taxIndex.txt");
        string taxIndexContents = "";
        taxIndexContents += "0\t-1\t0\tI\n";
        taxIndexContents += "1\t0\t1\tG\n";
        taxIndexContents += "2\t1\t2\tD\n";
        taxIndexContents += "3\t1\t2\tF\n";
        taxIndexContents += "4\t1\t2\tE\n";
        taxIndexContents += "5\t4\t3\tA\n";
        taxIndexContents += "6\t4\t3\tB\n";
        taxIndexContents += "7\t4\t3\tC\n";
        ofstream output(tax_index_path);
        output<<taxIndexContents;
        output.close();

        TaxSearch searcher(SeqToKMers(4,1), 2, false, 0, new SimpleTaxConsensus(LEVEL_NAMES), kmer_index_path,tax_index_path);
        BUTT_ASSERT_TRUE(false, "testIOException shouldnt reach this point");
    }catch(TaxSearchException e){
        BUTT_ASSERT_TRUE(true, "If you're here you're fine");
    }
    remove("temp_taxIndex.txt");

    try{
        string kmer_index_path("temp_kmerIndex.txt");
        string tax_index_path("randomNonexistingASDFpath.txt1");
        string kmerIndexContents = "";
        kmerIndexContents += "0\t0\t0\n";
        kmerIndexContents += "1\t0\t1\n";
        kmerIndexContents += "2\t0\t4\n";
        kmerIndexContents += "3\t0\t5;6\n";
        ofstream output(kmer_index_path);
        output<<kmerIndexContents;
        output.close();
        TaxSearch searcher(SeqToKMers(4,1), 2, false, 0, new SimpleTaxConsensus(LEVEL_NAMES), kmer_index_path,tax_index_path);
        BUTT_ASSERT_TRUE(false, "testIOException shouldnt reach this point");
    }catch(TaxSearchException e){
        BUTT_ASSERT_TRUE(true, "If you're here you're fine");
    }
    remove("temp_kmerIndex.txt");

    return true;
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

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0, new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq = "AAAA";

    set< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got "+to_string(nodes.size()));

    //BUTT_ASSERT_EQUALS("seqname", get<0>(h), "Sequence name should be seqname but is "+get<0>(h));
    //BUTT_ASSERT_EQUALS("I;G;E", get<1>(h), "Consensus should be I;G;E but is "+get<1>(h));
    //BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 nodes");

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


