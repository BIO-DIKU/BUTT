#ifndef TAXSEARCH_H
#define TAXSEARCH_H

#include <tuple>
#include <set>
#include <string>

#include "SeqToKMers.h"

/**
 * @brief A container for search-hit information used for return value of
 * TaxSearch::search.
 */
typedef std::tuple<std::string, int, std::string> Hit;

class TaxSearch
{
public:
    /**
     * @brief TaxSearch
     * @param seqSplitter
     * @param hits_max Include maximally this number of hits in the consensus.
     * @param best_only Include only the best scoring hits in the consensus.
     * That is if a hit consists of 344 kmers out of 345 possible, only hits with
     * 344 kmers are included.
     * @param coverage Filter hits based on kmer coverage. If a hit contains
     * fewer kmers than the total amount of kmers x coverage it will be filtered.
     */
    TaxSearch(SeqToKMers seqSplitter, int hits_max, bool best_only, double coverage);

    /**
     * @brief Method to search for a given sequence.
     * First the sequence is broken down into unique k-mers using the
     * seqSplitter.  For each taxonomic level starting from the deepest, all
     * nodes containing these k-mers are looked up. The nodes containing at
     * least a ratio of TaxSearch::coverage of the k-mers are considered hits.
     * If there are no hits at a taxonomic level, we move to the next level.
     *
     * If TaxSearch::best_only is set only the (at most TaxSearch::hits_max)
     * hits with maximum coverage are returned. Otherwise the (at most
     * TaxSearch::hits_max) hits with largest coverage (over
     * TaxSearch::coverage) are returned.
     * TODO: Rephrase a bit.
     * If there are no hits at the root level an empty set is returned.
     *
     * This function will only return non-empty results after
     * TaxSearch::readDatabases has been called.
     */
    std::set<Hit> search(std::string seqName, std::string sequence);

    /**
     * @brief Reads the index-files into data structure and prepare for the
     * search. If either the directory or files specified by prefix are non-
     * existing a FileNotFoundException will be raised.
     * @param directory
     * @param prefix
     */
    void readIndex(std::string &directory, std::string &prefix);
};

#endif // TAXSEARCH_H
