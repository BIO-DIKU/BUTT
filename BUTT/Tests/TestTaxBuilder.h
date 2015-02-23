#ifndef TESTTAXBUILDER_H
#define TESTTAXBUILDER_H

#include "TaxBuilder.h"

/**
 * @brief The TestTaxBuilder class
 * Following tests start with an empty TaxBuilder and each of the individual tests
 * are applied successively to the same object.
 */
class TestTaxBuilder
{
public:
    TestTaxBuilder();

    bool runTests();
private:

    TaxBuilder builder;

    /**
     * taxonomyString = "K#B;P#E"
     * sequence       = "AAGA"
     * kmer_size      = 3
     * step_size      = 1
     * Expected:
     * r        A
     *        /
     * K     B
     *     /
     * P  E
     * kmers(A)=kmers(B)={}
     * kmers(E)={AAG,AGA}
     */
    bool test1();

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
    bool test2();

    /**
     * taxonomyString = "K#B"
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
    bool test3();

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
    bool test4();


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
    bool test5();

};

#endif // TESTTAXBUILDER_H
