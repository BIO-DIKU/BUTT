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

TestTaxSearch::TestTaxSearch() {}

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
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 1", testSearchNodes1());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 2", testSearchNodes2());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 3", testSearchNodes3());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 4", testSearchNodes4());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 5", testSearchNodes5());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 6", testSearchNodes6());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 7", testSearchNodes7());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 8", testSearchNodes8());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 9", testSearchNodes9());
    BUTT_RUN_TEST("TestTaxSearch testSeachNode 10", testSearchNodes10());
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
                       seq_name+" but is " + get<0>(h));
    BUTT_ASSERT_EQUALS("Unclassified", get<1>(h),
                       "Consensus should be 'Unclassified' but is "
                       + get<1>(h));

    return true;
}

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
 * Expected: ("query_name", "Unclassified", 0) TODO: fix in doc
 */
bool TestTaxSearch::testSearchNodes1() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#a_1\n";
    tax_index_contents += "2\t0\t1\tK#a_1\n";
    tax_index_contents += "3\t0\t1\tK#a_2\n";
    tax_index_contents += "4\t0\t1\tK#z_7\n";
    tax_index_contents += "5\t2\t2\tP#b_1\n";
    tax_index_contents += "6\t2\t2\tP#b_1\n";
    tax_index_contents += "7\t2\t2\tP#b_2\n";
    tax_index_contents += "8\t2\t2\tP#y_8\n";
    tax_index_contents += "9\t6\t3\tC#c_1\n";
    tax_index_contents += "10\t6\t3\tC#c_1\n";
    tax_index_contents += "11\t6\t3\tC#c_2\n";
    tax_index_contents += "12\t6\t3\tC#x_9\n";

    string file1("temp_taxIndex.txt");
    string file2("temp_kmerIndex.txt");

    ofstream output(file1);
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1;2;3;4\n";
    kmer_index_contents += "2\t0\t5;6;7;8\n";
    kmer_index_contents += "3\t0\t9;10;11;12\n";

    output = ofstream(file2);
    output << kmer_index_contents;
    output.close();

    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file2, file1);

    remove(file1.c_str());
    remove(file2.c_str());

    string seq_name = "query_name";
    string seq      = "GGGG";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(0, nodes.size(), "Should have hit 0 nodes, got " +
                       to_string(nodes.size()));
    return true;
}

/**
 * Tests consensus of perfect hit
 * Input: kmers matching: c_1, c_1
 * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#c_1(100/100);O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes2() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#a_1\n";
    tax_index_contents += "2\t0\t1\tK#a_1\n";
    tax_index_contents += "3\t0\t1\tK#a_2\n";
    tax_index_contents += "4\t0\t1\tK#z_7\n";
    tax_index_contents += "5\t2\t2\tP#b_1\n";
    tax_index_contents += "6\t2\t2\tP#b_1\n";
    tax_index_contents += "7\t2\t2\tP#b_2\n";
    tax_index_contents += "8\t2\t2\tP#y_8\n";
    tax_index_contents += "9\t6\t3\tC#c_1\n";
    tax_index_contents += "10\t6\t3\tC#c_1\n";
    tax_index_contents += "11\t6\t3\tC#c_2\n";
    tax_index_contents += "12\t6\t3\tC#x_9\n";

    string file1("temp_taxIndex.txt");
    string file2("temp_kmerIndex.txt");

    ofstream output(file1);
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1;2;3;4\n";
    kmer_index_contents += "2\t0\t5;6;7;8\n";
    kmer_index_contents += "3\t0\t9;10\n";    // c_1, c_1
    kmer_index_contents += "3\t1\t11;12\n";   // c_2, x_9

    output = ofstream(file2);
    output << kmer_index_contents;
    output.close();

    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file2, file1);

    remove(file1.c_str());
    remove(file2.c_str());

    string seq_name = "query_name";
    string seq      = "AAAA";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(2, nodes.size(), "Should have hit 2 nodes, got " +
                       to_string(nodes.size()));

    BUTT_ASSERT_TRUE(10 == nodes[0] || 10 == nodes[1], "Failed to match 10");
    BUTT_ASSERT_TRUE(9  == nodes[0] || 9  == nodes[1], "Failed to match 9");

    return true;
}

/**
 * Tests consensus of hit down to C-level, first word
 * Input: kmers matching: c_1, c_2
 * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#C(100);O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes3() {
    // "#NODE_ID   PARENT_ID   LEVEL   NAME"
    string tax_index_contents = "";
    tax_index_contents += "0\t-1\t0\ti\n";
    tax_index_contents += "1\t0\t1\tK#a_1\n";
    tax_index_contents += "2\t0\t1\tK#a_1\n";
    tax_index_contents += "3\t0\t1\tK#a_2\n";
    tax_index_contents += "4\t0\t1\tK#z_7\n";
    tax_index_contents += "5\t2\t2\tP#b_1\n";
    tax_index_contents += "6\t2\t2\tP#b_1\n";
    tax_index_contents += "7\t2\t2\tP#b_2\n";
    tax_index_contents += "8\t2\t2\tP#y_8\n";
    tax_index_contents += "9\t6\t3\tC#c_1\n";
    tax_index_contents += "10\t6\t3\tC#c_1\n";
    tax_index_contents += "11\t6\t3\tC#c_2\n";
    tax_index_contents += "12\t6\t3\tC#x_9\n";

    string file1("temp_taxIndex.txt");
    string file2("temp_kmerIndex.txt");

    ofstream output(file1);
    output << tax_index_contents;
    output.close();

    // "#LEVEL   KMER   NODES"
    string kmer_index_contents = "";
    kmer_index_contents += "0\t0\t0\n";
    kmer_index_contents += "1\t0\t1;2;3;4\n";
    kmer_index_contents += "2\t0\t5;6;7;8\n";
    kmer_index_contents += "3\t0\t9\n";       // c_1
    kmer_index_contents += "3\t1\t10;11;12\n";   // c_1, c_2, x_9

    output = ofstream(file2);
    output << kmer_index_contents;
    output.close();

    TaxSearch searcher(SeqToKMers(4, 1), 2, false, 0,
                       new SimpleTaxConsensus(LEVEL_NAMES), file2, file1);

    remove(file1.c_str());
    remove(file2.c_str());

    string seq_name = "query_name";
    string seq      = "AAAA";

    vector< int > nodes = searcher.searchNodes(seq);

    BUTT_ASSERT_EQUALS(1, nodes.size(), "Should have hit 1 nodes, got " +
                       to_string(nodes.size()));

    BUTT_ASSERT_TRUE(9  == nodes[0] || 9  == nodes[1], "Failed to match 9");

    return true;
}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: c_1, x_9
 * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes4() {
    return false;
}

/**
 * Tests consensus of hit down to P-level, second word
 * Input: kmers matching: b_1, b_1
 * Expected: ("query_name", "K#a_1(100/100);P#b_1(100/100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes5() {
    return false;
}

/**
 * Tests consensus of hit down to P-level, first word
 * Input: kmers matching: b_1, b_2
 * Expected: ("query_name", "K#a_1(100/100);P#B(100);C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes6() {
    return false;
}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: b_1, y_8
 * Expected: ("query_name", "K#a_1(100/100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes7() {
    return false;
}

/**
 * Tests consensus of hit down to K-level, second word
 * Input: kmers matching: a_1, a_1
 * Expected: ("query_name", "K#a_1(100/100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes8() {
    return false;
}

/**
 * Tests consensus of hit down to K-level, first word
 * Input: kmers matching: a_1, a_2
 * Expected: ("query_name", "K#A(100);P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes9() {
    return false;
}

/**
 * Tests no consensus, but with hits
 * Input: kmers matching: a_1, z_7
 * Expected: ("query_name", "K#;P#;C#;O#;F#;G#;S#", 2)
 */
bool TestTaxSearch::testSearchNodes10() {
    return false;
}
