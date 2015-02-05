#ifndef SEQTOKMERS_H
#define SEQTOKMERS_H

#include <string>
#include <climits>

#include "Common.h"

/** @brief Exception thrown by SeqToKMers class. */
class SeqToKMerException: public std::exception {
public:
    SeqToKMerException(std::string &msg): exceptionMsg(msg){}
    SeqToKMerException(const SeqToKMerException &e): exceptionMsg(e.exceptionMsg){}
    const std::string exceptionMsg;
};


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
     * A SequenceToKMersException is thrown if kmer_size==0 or
     * kmer_size>sizeof(KMer)*CHAR_BIT/NUCL_BIT or step_size==0.
     * @param kmer_size The size of each k-mer
     * @param step_size The number of characters between the start of
     * adjacent k-mers
     */
    SeqToKMers(unsigned int kmer_size=8, unsigned int step_size=1);

    /**
     * @brief Convert the sequence to a set of unique k-mers using the
     * settings specified in the constructor.
     * Only k-mers of the sequence composed of the characters AUTCG (both
     * upper/lower case permitted) are returned. All T-characters will
     * be converted to U characters.
     */
    KMerSet sequenceToKMers(std::string &sequence);

private:
    unsigned int kmer_size;
    unsigned int step_size;

    unsigned int decodeKMer(std::string &sequence, unsigned int pos, KMer &buffer, int suffixSz);
};

#endif // SEQTOKMERS_H
