#ifndef SEQTOKMERS_H
#define SEQTOKMERS_H

#include <string>

#include "Common.h"


/**
 * @brief Class for converting a sequence string into a set of k-mers.
 * The sequence is split into k-mers all of the same size. A step-argument
 * can be used to indicate the number of characters the start of one k-mer
 * and the next.
 */
class SeqToKMers
{
public:

    /**
     * @brief Prepare a sequence-to-kmer conversion.
     * @param kmer_size The size of each k-mer
     * @param step_size The number of characters between the start of
     * adjacent k-mers
     */
    SeqToKMers(unsigned int kmer_size=8, unsigned int step_size=1);

    /**
     * @brief Convert the sequence to a set of k-mers using the settings
     * specified in the constructor. Only k-mers of the sequence containing
     * the characters AUTCG (both upper/lower case permitted) are returned.
     */
    KMerSet sequenceToKMers(std::string sequence);

private:
    unsigned int kmer_size;
    unsigned int step_size;
};

#endif // SEQTOKMERS_H
