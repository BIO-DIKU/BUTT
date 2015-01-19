#ifndef SEQTOKMERS_H
#define SEQTOKMERS_H

#include <string>

#include "Common.h"


/**
 * @brief Class for converting a sequence string into a set of k-mers.
 * The sequence is split into k-mers all of the same size. A step-argument
 * can be used to
 */
class SeqToKMers
{
public:

    SeqToKMers(unsigned int kmer_size=8, unsigned int step_size=1);

    KMerSet sequenceToKMers(string sequence);

private:
    unsigned int kmer_size;
    unsigned int step_size;
};

#endif // SEQTOKMERS_H
