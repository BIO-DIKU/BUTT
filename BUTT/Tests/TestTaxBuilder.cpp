#include "TestTaxBuilder.h"

#include <iostream>
#include <fstream>
#include <string>

#include "TaxBuilder.h"
#include "SeqToKMers.h"
#include "TestHelper.h"

TestTaxBuilder::TestTaxBuilder():
    builder(SeqToKMers(3,1))
{

}

bool TestTaxBuilder::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestTaxBuilder test 1", test1());
    BUTT_RUN_TEST("TestTaxBuilder test 2", test2());
    BUTT_RUN_TEST("TestTaxBuilder test 3", test3());
    BUTT_RUN_TEST("TestTaxBuilder test 4", test4());
    BUTT_RUN_TEST("TestTaxBuilder test 5", test5());
    BUTT_RUN_TEST("TestTaxBuilder test 6", test6());
    BUTT_POST_TESTS();

}

bool TestTaxBuilder::test1()
{
    builder.addTaxEntry("K#B;P#E;C#", "AAGA");

    BUTT_ASSERT_EQUALS(3, builder.treeSize(), "Bad treeSize. Expected 3, was "+std::to_string(builder.treeSize()));
    BUTT_ASSERT_EQUALS("root", builder.getNode(0).getName(), "Root name mismatch");
    BUTT_ASSERT_EQUALS("K#B", builder.getNode(1).getName(), "Kingdom name mismatch");
    BUTT_ASSERT_EQUALS("P#E", builder.getNode(2).getName(), "Phylum name mismatch");
    BUTT_ASSERT_EQUALS(3, builder.treeSize(), "Bad treeSize. Expected 3, was "+std::to_string(builder.treeSize()));

    BUTT_ASSERT_EQUALS(0, builder.getNode(1).getParent().node_id, "Node 0 should be parent of 1");
    BUTT_ASSERT_EQUALS(1, builder.getNode(2).getParent().node_id, "Node 1 should be parent of 2");

    BUTT_ASSERT_EQUALS(0, builder.getNode(0).getKMers().size(), "Node 0 should have no K-mers");
    BUTT_ASSERT_EQUALS(0, builder.getNode(1).getKMers().size(), "Node 1 should have no K-mers");
    BUTT_ASSERT_EQUALS(2, builder.getNode(2).getKMers().size(), "Node 2 should have 2 K-mers");

    return true;
}


    /**
     * taxonomyString = "K#B;P#F"
     * sequence       = "AAGU"
     * kmer_size      = 3
     * step_size      = 1
     * Expected:
     * r        A
     *        /
     * K     B
     *     /   \
     * P  E     F
     * kmers(A)=kmers(B)={}
     * kmers(E)={AAG,AGA}
     * kmers(F)={AAG,AGU}
     */
bool TestTaxBuilder::test2()
{
    builder.addTaxEntry("K#B;P#F;C#", "AAGU");

    BUTT_ASSERT_EQUALS(4, builder.treeSize(), "Bad treeSize. Expected 4, was "+std::to_string(builder.treeSize()));
    BUTT_ASSERT_EQUALS("P#F", builder.getNode(3).getName(), "New nodes name should be P#F");

    BUTT_ASSERT_EQUALS(1, builder.getNode(3).getParent().node_id, "Node 1 should be parent of 3");

    BUTT_ASSERT_EQUALS(0, builder.getNode(1).getKMers().size(), "Node 1 should have no K-mers");
    BUTT_ASSERT_EQUALS(2, builder.getNode(3).getKMers().size(), "Node 3 should have 2 K-mers");

    return true;
}


/**
 * taxonomyString = "K#B;P#"
 * sequence       = "AAG"
 * kmer_size      = 3
 * step_size      = 1
 * Expected:
 * r        A
 *        /
 * K     B
 *     /   \
 * P  E     F
 * kmers(A)={}
 * kmers(B)={AAG}
 * kmers(E)={AAG,AGA}
 * kmers(F)={AAG,AGU}
 */
bool TestTaxBuilder::test3()
{
    builder.addTaxEntry("K#B;P#;C#", "AAG");

    BUTT_ASSERT_EQUALS(4, builder.treeSize(), "Bad treeSize. Expected 4, was "+std::to_string(builder.treeSize()));
    BUTT_ASSERT_EQUALS(0, builder.getNode(0).getKMers().size(), "Node 0 should have 0 K-mers");
    BUTT_ASSERT_EQUALS(1, builder.getNode(1).getKMers().size(), "Node 1 should have 1 K-mer");
    BUTT_ASSERT_EQUALS(2, builder.getNode(2).getKMers().size(), "Node 2 should have 2 K-mers");
    BUTT_ASSERT_EQUALS(2, builder.getNode(3).getKMers().size(), "Node 3 should have 2 K-mers");

    return true;
}

/**
 * taxonomyString = "K#B;P#E;C#G"
 * sequence       = "AAGAG"
 * kmer_size      = 3
 * step_size      = 1
 * Expected:
 * r             A
 *             /
 * K          B
 *          /   \
 * P       E     F
 *       /
 * C    G
 * kmers(A)={}
 * kmers(B)={AAG}
 * kmers(E)={AAG,AGA}
 * kmers(F)={AAG,AGU}
 * kmers(G)={AAG,AGA,GAG}
 */
bool TestTaxBuilder::test4()
{
    builder.addTaxEntry("K#B;P#E;C#G", "AAGAG");

    BUTT_ASSERT_EQUALS(5, builder.treeSize(), "Bad treeSize. Expected 5, was "+std::to_string(builder.treeSize()));
    BUTT_ASSERT_EQUALS(2, builder.getNode(2).getKMers().size(), "Node 2 should have 2 K-mers");
    BUTT_ASSERT_EQUALS(3, builder.getNode(4).getKMers().size(), "Node 4 should have 3 K-mers");

    return true;
}

/**
 * Input:
 * r             A
 *             /
 * K          B
 *          /   \
 * P       E     F
 *       /
 * C    G
 * kmers(A)={}
 * kmers(B)={AAG}
 * kmers(E)={AAG,AGA}
 * kmers(F)={AAG,AGU}
 * kmers(G)={AAG,AGA,GAG}
 * After pullUnions we expect:
 * kmers(A)={AAG,AGA,AGU,GAG}
 * kmers(B)={AAG,AGA,AGU,GAG}
 * kmers(E)={AAG,AGA,GAG}
 * kmers(F)={AAG,AGU}
 * kmers(G)={AAG,AGA,GAG}
 */
bool TestTaxBuilder::test5()
{
    builder.pullUnions(*builder.root);
    BUTT_ASSERT_EQUALS(4, builder.getNode(0).getKMers().size(), "Node 0 should have 4 K-mers");
    BUTT_ASSERT_EQUALS(4, builder.getNode(1).getKMers().size(), "Node 1 should have 4 K-mers");
    BUTT_ASSERT_EQUALS(3, builder.getNode(2).getKMers().size(), "Node 2 should have 3 K-mers");
    BUTT_ASSERT_EQUALS(2, builder.getNode(3).getKMers().size(), "Node 3 should have 2 K-mers");
    BUTT_ASSERT_EQUALS(3, builder.getNode(4).getKMers().size(), "Node 4 should have 3 K-mers");
    return true;
}


/**
 * Input:
 * r             A
 *             /
 * K          B
 *          /   \
 * P       E     F
 *       /
 * C    G
 * kmers(A)={}
 * kmers(B)={AAG}
 * kmers(E)={AAG,AGA}
 * kmers(F)={AAG,AGU}
 * kmers(G)={AAG,AGA,GAG}
 * After saveTaxIndex("taxIndex.txt") we expect the following file to exist
 * and contain:
 * taxIndex.txt:
 * #NODE_ID	LEVEL	NAME	PARENT_ID
 * 0	0	root	-1
 * 1	1	K#B	0
 * 2	2	P#E	1
 * 3	2	P#F	1
 * 4	3	C#G	2
 * kmerIndex.txt:
 * #LEVEL	KMER	NODES
 * 0	AAG	0
 * 0	AGA	0
 * 0	AGU	0
 * 0	GAG	0
 * 1	AAG	1
 * 1	AGA	1
 * 1	AGU	1
 * 1	GAG	1
 * 2	AAG	2;3
 * 2	AGA	2
 * 2	AGU	3
 * 2	GAG	2
 * 3	AAG	4
 * 3	AGA	4
 * 3	GAG	4
 */
bool TestTaxBuilder::test6()
{
    std::string file("taxIndex.txt");
    builder.saveTaxIndex(file);

    std::vector<std::string> expectedLines = {
        "#NODE_ID\tLEVEL\tNAME\tPARENT_ID",
        "0\t0\troot\t-1",
        "1\t1\tK#B\t0",
        "2\t2\tP#E\t1",
        "4\t3\tC#G\t2",
        "3\t2\tP#F\t1"
    };

    std::ifstream input("taxIndex.txt");
    std::string line;
    int lineNum = 0;
    while(std::getline(input,line)){
        BUTT_ASSERT_EQUALS(expectedLines[lineNum], line, "Line mismatch. Expected \""+expectedLines[lineNum]+"\" was \""+line+"\"");
        lineNum++;
    }

}


/**
 * Input:
 * r             A
 *             /
 * K          B
 *          /   \
 * P       E     F
 *       /
 * C    G
 * kmers(A)={}
 * kmers(B)={AAG}
 * kmers(E)={AAG,AGA}
 * kmers(F)={AAG,AGU}
 * kmers(G)={AAG,AGA,GAG}
 * After saveKMerIndex("kmerIndex.txt") we expect the file to contain:
 * #LEVEL	KMER	NODES
 * 0	AAG	0
 * 0	AGA	0
 * 0	AGU	0
 * 0	GAG	0
 * 1	AAG	1
 * 1	AGA	1
 * 1	AGU	1
 * 1	GAG	1
 * 2	AAG	2;3
 * 2	AGA	2
 * 2	AGU	3
 * 2	GAG	2
 * 3	AAG	4
 * 3	AGA	4
 * 3	GAG	4
 */
bool TestTaxBuilder::test6()
{
    std::string file("taxIndex.txt");
    builder.saveTaxIndex(file);

    std::vector<std::string> expectedLines = {
        "#",
        "0\t0\troot\t-1",
        "1\t1\tK#B\t0",
        "2\t2\tP#E\t1",
        "3\t2\tP#F\t1",
        "4\t3\tC#G\t2"
    };

    std::ifstream input("taxIndex.txt");
    std::string line;
    int lineNum = 0;
    while(std::getline(input,line)){
        BUTT_ASSERT_EQUALS(expectedLines[lineNum], line, "Line mismatch. Expected \""+expectedLines[lineNum]+"\" was \""+line+"\"");
    }

}
