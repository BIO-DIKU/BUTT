#include "TestSeqToKMers.h"

#include <iostream>
#include <iterator> //advance

#include "Tests/TestHelper.h"
#include "SeqToKMers.h"



TestSeqToKMers::TestSeqToKMers()
{

}

bool TestSeqToKMers::runTests()
{
    BUTT_PRE_TESTS();
    BUTT_RUN_TEST("TestSeqToKMers test 1", test1());
    BUTT_RUN_TEST("TestSeqToKMers test 2", test2());
    BUTT_RUN_TEST("TestSeqToKMers test 3", test3());
    BUTT_RUN_TEST("TestSeqToKMers test 4", test4());
    BUTT_RUN_TEST("TestSeqToKMers test 5", test5());
    BUTT_RUN_TEST("TestSeqToKMers test 6", test6());
    BUTT_RUN_TEST("TestSeqToKMers test 7", test7());
    BUTT_RUN_TEST("TestSeqToKMers test 8", test8());
    BUTT_RUN_TEST("TestSeqToKMers test 9", test9());
    BUTT_RUN_TEST("TestSeqToKMers test 10", test10());
    BUTT_POST_TESTS();

}

/**
 * sequence = ATCG
 * kmer_size = 17
 * step_size = 1
 * Expects SeqToKMerException
 */
bool TestSeqToKMers::test1()
{
    try{
        SeqToKMers convert(17 ,1);
        BUTT_ASSERT_FALSE(true, "Exception not thrown");
    }catch(SeqToKMerException e){
        BUTT_ASSERT_TRUE(true, "Expects exception");
        return true;
    }
    return false;
}

/**
 * sequence = ATCG
 * kmer_size = 1
 * step_size = 0
 * Expects SeqToKMerException
 */
bool TestSeqToKMers::test2()
{
    try{
        SeqToKMers convert(1 ,0);
        BUTT_ASSERT_FALSE(true, "Exception not thrown");
    }catch(SeqToKMerException e){
        BUTT_ASSERT_TRUE(true, "Expects exception");
        return true;
    }
    return false;

}


/**
 * sequence = ATCG
 * kmer_size = 0
 * step_size = 1
 * Expects SeqToKMerException
 */
bool TestSeqToKMers::test3()
{
    try{
        SeqToKMers convert(0 ,1);
        BUTT_ASSERT_FALSE(true, "Exception not thrown");
    }catch(SeqToKMerException e){
        BUTT_ASSERT_TRUE(true, "Expects exception");
        return true;
    }
    return false;

}

const KMer &TestSeqToKMers::get(KMerSet &set, int elem)
{
    auto it = set.begin();
    std::advance(it, elem);
    return *it;
}

/**
* sequence = ATCGUatcgu
* kmer_size = 1
* step_size = 1
* Expects: A,C,G,U
*/
bool TestSeqToKMers::test4(){
    SeqToKMers convert(1,1);

    std::string seq("ATCGUatcgu");
    KMerSet set = convert.sequenceToKMers(seq);
    //KMerSet set = convert.sequenceToKMers(std::string("ATCGUatcgu"));
    BUTT_ASSERT_EQUALS(4, set.size(), "K-mer set size should be 4 (is "+std::to_string(set.size())+")");
    BUTT_ASSERT_EQUALS(NUCL_A, get(set, 0), "A is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_C, get(set, 1), "C is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_G, get(set, 2), "G is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_U, get(set, 3), "U is not in k-mer set");
    return true;
}


/**
 * sequence = ATCC
 * kmer_size = 2
 * step_size = 1
 * Expects: AU,CC,UC
 */
bool TestSeqToKMers::test5()
{
    unsigned int AU = (NUCL_A<<2)|(NUCL_U<<0);
    unsigned int CC = (NUCL_C<<2)|(NUCL_C<<0);
    unsigned int UC = (NUCL_U<<2)|(NUCL_C<<0);
    SeqToKMers convert(2,1);
    std::string seq("ATCC");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(AU, get(set, 0), "AU is not in k-mer set");
    BUTT_ASSERT_EQUALS(CC, get(set, 1), "CC is not in k-mer set");
    BUTT_ASSERT_EQUALS(UC, get(set, 2), "UC is not in k-mer set");

    return true;

}

/**
 * sequence = ATCC
 * kmer_size = 5
 * step_size = 1
 * Expects: {}
 */
bool TestSeqToKMers::test6()
{
    SeqToKMers convert(5,1);
    std::string seq("ATCC");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(0, set.size(), "k-mer set not empty");

    return true;
}

/**
 * sequence = ATCG
 * kmer_size = 1
 * step_size = 2
 * Expects: A,C
 */
bool TestSeqToKMers::test7()
{
    SeqToKMers convert(1,2);
    std::string seq("ATCG");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(2, set.size(), "K-mer set size should be 2 (is "+std::to_string(set.size())+")");
    BUTT_ASSERT_EQUALS(NUCL_A, get(set, 0), "A is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_C, get(set, 1), "C is not in k-mer set");

    return true;
}

/**
 * sequence = ATCGU
 * kmer_size = 1
 * step_size = 2
 * Expects: A,C,U
 */
bool TestSeqToKMers::test8()
{
    SeqToKMers convert(1,2);
    std::string seq("ATCGU");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(3, set.size(), "K-mer set size should be 3 (is "+std::to_string(set.size())+")");
    BUTT_ASSERT_EQUALS(NUCL_A, get(set, 0), "A is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_C, get(set, 1), "C is not in k-mer set");
    BUTT_ASSERT_EQUALS(NUCL_U, get(set, 2), "U is not in k-mer set");

    return true;
}

/**
 * sequence = ATCG
 * kmer_size = 1
 * step_size = 4
 * Expects: A
 */
bool TestSeqToKMers::test9()
{
    SeqToKMers convert(1,4);
    std::string seq("ATCG");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(1, set.size(), "K-mer set size should be 1 (is "+std::to_string(set.size())+")");
    BUTT_ASSERT_EQUALS(NUCL_A, get(set, 0), "A is not in k-mer set");

    return true;
}

/**
 * sequence = AnCG
 * kmer_size = 2
 * step_size = 1
 * Expects: CG
 */
bool TestSeqToKMers::test10()
{
    SeqToKMers convert(2,1);
    std::string seq("AnCG");
    KMerSet set = convert.sequenceToKMers(seq);
    BUTT_ASSERT_EQUALS(1, set.size(), "K-mer set size should be 1 (is "+std::to_string(set.size())+")");
    BUTT_ASSERT_EQUALS( (NUCL_C<<2)|(NUCL_G) , get(set, 0), "CG is not in k-mer set");

    return true;
}
