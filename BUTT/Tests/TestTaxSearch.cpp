/* Copyright 2015 BIO-DIKU */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "TestTaxSearch.h"
#include "TestHelper.h"
#include "Search/TaxSearch.h"
#include "Search/SimpleTaxConsensus.h"

#define LEVEL_NAMES {"K", "P", "C", "O", "F", "G", "S"}

#define NODES_FIND(x) (find(nodes.begin(), nodes.end(), x) != nodes.end())

using namespace std;

TestTaxSearch::TestTaxSearch() {
}

bool TestTaxSearch::runTests() {
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
    BUTT_RUN_TEST("TestTaxSearch test 9", test9());
    BUTT_POST_TESTS();
}

bool TestTaxSearch::testIOExceptions() {
    try {
        string kmer_index_path("randomNonexistingASDFpath.txt1");
        string tax_index_path("temp_taxIndex.txt");
        string tax_index_contents = "";
        tax_index_contents += "0\t-1\t0\tI\n";
        tax_index_contents += "1\t0\t1\tG\n";
        tax_index_contents += "2\t1\t2\tD\n";
        tax_index_contents += "3\t1\t2\tF\n";
        tax_index_contents += "4\t1\t2\tE\n";
        tax_index_contents += "5\t4\t3\tA\n";
        tax_index_contents += "6\t4\t3\tB\n";
        tax_index_contents += "7\t4\t3\tC\n";
        ofstream output(tax_index_path);
        output << tax_index_contents;
        output.close();

        TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                           new SimpleTaxConsensus(LEVEL_NAMES), kmer_index_path,
                           tax_index_path);
        BUTT_ASSERT_TRUE(false, "testIOException shouldnt reach this point");
    } catch(TaxSearchException e) {
        BUTT_ASSERT_TRUE(true, "If you're here you're fine");
    }

    remove("temp_taxIndex.txt");

    try {
        string kmer_index_path("temp_kmerIndex.txt");
        string tax_index_path("randomNonexistingASDFpath.txt1");
        string kmer_index_contents = "";
        kmer_index_contents += "0\t0\t0\n";
        kmer_index_contents += "1\t0\t1\n";
        kmer_index_contents += "2\t0\t4\n";
        kmer_index_contents += "3\t0\t5;6\n";
        ofstream output(kmer_index_path);
        output << kmer_index_contents;
        output.close();
        TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                           new SimpleTaxConsensus(LEVEL_NAMES),
                           kmer_index_path, tax_index_path);
        BUTT_ASSERT_TRUE(false, "testIOException shouldnt reach this point");
    } catch(TaxSearchException e) {
        BUTT_ASSERT_TRUE(true, "If you're here you're fine");
    }

    remove("temp_kmerIndex.txt");

    return true;
}

/*
 * test-cases for testSearchNodes.
 * The following tree-layout is used for test1-test9
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
bool TestTaxSearch::test1() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAA";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));
    BUTT_ASSERT_TRUE(NODES_FIND(5), "Node 5 not found in nodes");
    BUTT_ASSERT_TRUE(NODES_FIND(6), "Node 6 not found in nodes");

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 nodes");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is " + get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

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
bool TestTaxSearch::test2() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";
    kmer_index_contents += "3\t1\t5;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAAC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));
    BUTT_ASSERT_TRUE(NODES_FIND(5), "Node 5 not found in nodes");
    BUTT_ASSERT_TRUE(NODES_FIND(7), "Node 7 not found in nodes");

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 nodes");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is " + get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests that hits are sorted (together with test2)
 * hits_max = 2
 * best_only = false
 * Query hits only: A, B, C, E, G, I
 * hits(B)>hits(A)>hits(C)
 * Expected: {B,A}
 */
bool TestTaxSearch::test3() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";
    kmer_index_contents += "3\t1\t5;6\n";
    kmer_index_contents += "3\t9\t6\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                                  new SimpleTaxConsensus(LEVEL_NAMES), file1,
                                  file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAACC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));
    BUTT_ASSERT_TRUE(nodes[0] == 6, "Node 6 not first hit");
    BUTT_ASSERT_TRUE(nodes[1] == 5, "Node 5 not second hit");

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 nodes");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is " + get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests best_only
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(B)>hits(A)>hits(C)
 * Expected: {B}
 */
bool TestTaxSearch::test4() {
    // "#NODE_ID   PARENT_I   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";
    kmer_index_contents += "3\t1\t6\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, true, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAAC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(1, nodes.size(), "Should have hit 1 nodes, got " +
                       to_string(nodes.size()));
    BUTT_ASSERT_TRUE(nodes[0] == 6, "Node 6 not found in nodes");

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(1, get<2>(h), "Should have hit 1 node");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is " + get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#b;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#b;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests best_only with multple best hits.
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(A)=hits(B)>hits(C)
 * Expected: {A,B}
 */
bool TestTaxSearch::test5() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";
    kmer_index_contents += "3\t1\t6;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, true, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAAC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));
    BUTT_ASSERT_TRUE(NODES_FIND(6), "Node 6 not found in nodes");
    BUTT_ASSERT_TRUE(NODES_FIND(7), "Node 7 not found in nodes");

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 node");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is "+get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests best_only when there are more than hits_max hits
 * hits_max = 2
 * best_only = true
 * Query hits only: A, B, C, E, G, I
 * hits(A)=hits(B)=hits(C)
 * Expected: {A,B}|{A,C}|{B,C} (2 nodes only tested)
 */
bool TestTaxSearch::test6() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, true, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAAC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(2, get<2>(h), "Should have hit 2 node");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is "+get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests hits_max > hits return OK.
 * hits_max = 5
 * best_only = false
 * Query hits only: A, B, C, E, G, I
 * hits(A)=hits(B)=hits(C)
 * Expected: 3 hits
 */
bool TestTaxSearch::test7() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 5, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAAC";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(3, nodes.size(), "Should have hit 3 nodes, got " +
                       to_string(nodes.size()));

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(3, get<2>(h), "Should have hit 3 nodes");

    return true;
}

/**
 * Tests hits on second level
 * hits_max = 2
 * best_only = false
 * Query hits only: E, G, I
 * Expected: {E}
 */
bool TestTaxSearch::test8() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t1\t5;6;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "AAAA";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(1, nodes.size(), "Should have hit 1 node, got " +
                       to_string(nodes.size()));

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(1, get<2>(h), "Should have hit 1 node");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name + " but is "+get<0>(h));
    BUTT_ASSERT_EQUALS("K#g;P#e;C#;O#;F#;G#;S#", get<1>(h),
                       "Consensus should be K#g;P#e;C#;O#;F#;G#;S# but is " +
                       get<1>(h));

    return true;
}

/**
 * Tests that empty vector is returned if no hits
 * hits_max = 2
 * best_only = false
 * Query hits only: {}
 * Expected: {}
 */
bool TestTaxSearch::test9() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#g\n";
    tax_index_contents += "2\t1\t2\tP#d\n";
    tax_index_contents += "3\t1\t2\tP#f\n";
    tax_index_contents += "4\t1\t2\tP#e\n";
    tax_index_contents += "5\t4\t3\tC#a\n";
    tax_index_contents += "6\t4\t3\tC#b\n";
    tax_index_contents += "7\t4\t3\tC#c\n";

    ofstream output("temp_taxIndex.txt");
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1\n";
    kmer_index_contents += "2\t0\t4\n";
    kmer_index_contents += "3\t0\t5;6;7\n";

    output = ofstream("temp_kmerIndex.txt");
    output << kmer_index_contents;
    output.close();

    string file1("temp_kmerIndex.txt");
    string file2("temp_taxIndex.txt");
    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file1, file2);
    remove("temp_kmerIndex.txt");
    remove("temp_taxIndex.txt");

    string seq_name = "seqname";
    string seq      = "GGGG";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(0, nodes.size(), "Should have hit 0 nodes, got " +
                       to_string(nodes.size()));

    Hit h = searcher.search(seq_name, seq);

    BUTT_ASSERT_EQUALS(0, get<2>(h), "Should have hit 0 nodes");
    BUTT_ASSERT_EQUALS(seq_name, get<0>(h), "Sequence name should be " +
                       seq_name+" but is "+get<0>(h));
    BUTT_ASSERT_EQUALS("Unclassified", get<1>(h),
                       "Consensus should be 'Unclassified' but is "+get<1>(h));

    return true;
}
