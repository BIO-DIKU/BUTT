#ifndef TAXLEVEL_H
#define TAXLEVEL_H

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

// /**
//  * @brief Exception thrown by TaxSearch class
//  */
// class TaxSearchException: public std::exception {
// public:
//     TaxSearchException(std::string &&msg): exceptionMsg(msg){}
//     TaxSearchException(const TaxSearchException &e): exceptionMsg(e.exceptionMsg){}
//     const std::string exceptionMsg;
// };

class TaxLevel
{
public:
    /**
     * @brief Constructor for empty TaxLevel object.
     * @param Oligo size k.
     */
    TaxLevel(int k);

    /**
     * @brief For a given kmer set update the nodes histogram.
     */
    void update_nodes_hist(std::vector<unsigned int>&hist, KMerSet& kmers);

    /**
     * @brief Add given node to kmer list.
     */
    void add_node_to_kmer(int node, KMer kmer);

private:

    std::vector< std::list<int> > kmer_to_node_vec;
};

#endif // TAXLEVEL_H
