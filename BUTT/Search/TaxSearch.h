#ifndef TAXSEARCH_H
#define TAXSEARCH_H

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
     * Method to execute a search for a given sequence entry. First the
     * sequence is broken down into unique kmers of a given kmer_size
     * overlapping with a given step_size. See Taxonomy::Index.add.
     * Now, for each taxonomic level, starting from species all nodes
     * for each kmer is looked up in the database. The nodes containing
     * most kmers are considered hits. If there are no hits at a taxonomic
     * level, we move to the next level. Hits are sorted according to how
     * many kmers matched this particular node and a consensus taxonomy
     * string is determined. Hits are also filtered with the following
     * options:
     * hits_max  -
     * best_only -
     * coverage  -

    void readDatabases(std::string &directory, std::string &prefix);
};

#endif // TAXSEARCH_H
