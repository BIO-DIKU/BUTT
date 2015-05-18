#ifndef TAXSEARCH_H
#define TAXSEARCH_H

#include <tuple>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include "Common.h"
#include "Search/NameNode.h"
#include "Search/TaxConsensus.h"
#include "SeqToKMers.h"
#include "Search/TaxLevel.h"

/**
 * @brief Exception thrown by TaxSearch class
 */
class TaxSearchException: public std::exception {
public:
    TaxSearchException(std::string &&msg): exceptionMsg(msg){}
    TaxSearchException(const TaxSearchException &e): exceptionMsg(e.exceptionMsg){}
    const std::string exceptionMsg;
};

/**
 * @brief A container for search-hit information used for return value of
 * TaxSearch::search.
 * The first string represents the seqName provided for a search.
 * The second string represents the consensus taxonomy string of the search
 * results.
 * The integer indicates the number of node-hits that were used to compile the
 * consensus (at most hits_max).
 */
typedef std::tuple<std::string, std::string, int> Hit;
std::ostream & operator<<(std::ostream & os, Hit hit);

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
     * @param kmer_index_path File path for the kmer index file
     * @param tax_index_path File path for the taxonomy index file
     * fewer kmers than the total amount of kmers x coverage it will be filtered.
     */
    TaxSearch(SeqToKMers seqSplitter, int hits_max, bool best_only, double coverage, TaxConsensus* consensus_builder, std::string &kmer_index_path, std::string &tax_index_path);

    /**
     * @brief Perform a BUTT search using searchNodes and compile a consensus
     * taxonomy string.
     * @param seqName a sequence name (not used in search).
     * @param sequence the query-sequence
     *
     * @return a tuple containing the seqName and consensus string.
     * Example:
     * ("Query 1","K#Bacteria(100);P#Proteobacteria(100);C#Gammaproteobacteria(80);O#Vibrionales(75);F#;G#;S#")
     */
    Hit search(std::string &seqName, std::string &sequence);


    /// R-value version of search function for convenience and tests
    Hit search(std::string &&seqName, std::string &&sequence);


    /**
     * @brief Method to search for a given sequence.
     * First the sequence is broken down into unique k-mers using the
     * seqSplitter.  For each taxonomic level starting from the deepest, all
     * nodes containing these k-mers are looked up. The nodes containing at
     * least a ratio of TaxSearch::coverage of the k-mers are considered node-hits.
     * If there are no node-hits at a taxonomic level, we move to the next level.
     *
     * If TaxSearch::best_only is set, only the (at most TaxSearch::hits_max)
     * node-hits with maximum coverage are returned. Otherwise the (at most
     * TaxSearch::hits_max) hits with largest coverage (over
     * TaxSearch::coverage) are returned.
     *
     * If there are no node-hits at the root level an empty set is returned.
     *
     * This function will only return non-empty results after
     * TaxSearch::readDatabases has been called. The values in the set are
     * indices of nodes in the node-tree.
     */
    std::set<int> searchNodes(std::string &sequence);

private:
    const SeqToKMers seq_splitter;
    const int hits_max;
    const bool best_only;
    const double coverage;
    TaxConsensus* consensus_builder;
    std::vector<NameNode> nodes;
    std::vector< std::string > level_names;

    /// Vector with levels.
    std::vector< TaxLevel > level_vector;

    /// Working memory for building histograms in search. Arrays are used in the hope
    /// that memset will be faster than vector::assign.
    std::vector<unsigned int> node_counts;

    /**
     * @brief Reads the taxonomy index files into data structure and prepare for the
     * search. If the file does not exist, a FileNotFoundException will be raised.
     * @param file_path
     */
    void readTaxIndex(std::string &file_path);

    /**
     * @brief Reads the kmer index files into data structure and prepare for the
     * search. If the file does not exist, a FileNotFoundException will be raised.
     * @param file_path
     */
    void readKMerIndex(std::string &file_path);

    /**
     * @brief Given a node ID find the node in the taxonomy tree and collect 
     * node names from the node ID to the root.
     * @param node_id
     * @param node_tax_row Vector for returning names.
     */
    void fill_node_tax_row(int node_id, std::vector<std::string> &node_tax_row);

    static bool descendingSortOrder(unsigned int a, unsigned int b){ return a > b; }

    static bool descendingPairSortOrder(const std::pair<int, int> &a, const std::pair<int, int> &b) {
        return a.second > b.second;
    }

    void pickBestHits(std::set<int> &ret, int kmer_size);

    void readTaxLevelNames();
};

#endif // TAXSEARCH_H
