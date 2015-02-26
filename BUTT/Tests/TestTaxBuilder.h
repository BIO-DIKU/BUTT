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
     * After saveIndex("taxIndex.txt", "kmerIndex.txt") we expect the two files to exist
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
    bool test6();

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
    bool test7();
    /**
     * Input:
     * r             A
     *             /   \
     * K          B     D
     *          /   \    \
     * P       C     F    E
     * kmers(A)={AA}
     * kmers(B)={AA}
     * kmers(E)={AA}
     * kmers(F)={AA}
     * kmers(G)={AA}
     * After saveKMerIndex("kmerIndex.txt") we expect the file to contain:
     * #LEVEL	KMER	NODES
     * 0	AA	0
     * 1	AA	1;3
     * 2	AA	2;4;5
     */
    bool test8();
};

#endif // TESTTAXBUILDER_H
