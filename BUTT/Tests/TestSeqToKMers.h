#ifndef TESTSEQTOKMERS_H
#define TESTSEQTOKMERS_H

#include "Common.h"

class TestSeqToKMers
{
public:
    TestSeqToKMers();

    bool runTests();


private:
    bool testSeqToKMers();
    bool testSequenceToKMers();

    const KMer &get(KMerSet &set, int elem);


    /**
     * sequence = ATCG
     * kmer_size = 17
     * step_size = 1
     * Expects SeqToKMerException
     */
    bool test1();

    /**
     * sequence = ATCG
     * kmer_size = 1
     * step_size = 0
     * Expects SeqToKMerException
     */
    bool test2();

    /**
     * sequence = ATCG
     * kmer_size = 0
     * step_size = 1
     * Expects SeqToKMerException
     */
    bool test3();

    /**
     * sequence = ATCGUatcgu
     * kmer_size = 1
     * step_size = 1
     * Expects: A,C,G,U
     */
    bool test4();

    /**
     * sequence = ATCC
     * kmer_size = 2
     * step_size = 1
     * Expects: AU,CC,UC
     */
    bool test5();

    /**
     * sequence = ATCC
     * kmer_size = 5
     * step_size = 1
     * Expects: {}
     */
    bool test6();

    /**
     * sequence = ATCG
     * kmer_size = 1
     * step_size = 2
     * Expects: A,C
     */
    bool test7();

    /**
     * sequence = ATCGU
     * kmer_size = 1
     * step_size = 2
     * Expects: A,C,U
     */
    bool test8();

    /**
     * sequence = ATCG
     * kmer_size = 1
     * step_size = 4
     * Expects: A
     */
    bool test9();

    /**
     * sequence = AnCG
     * kmer_size = 2
     * step_size = 1
     * Expects: CG
     */
    bool test10();
};

#endif // TESTSEQTOKMERS_H
