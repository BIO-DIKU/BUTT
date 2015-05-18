#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "TaxSearch.h"
#include "Common.h"
#include "Search/TaxLevel.h"

using namespace std;

TaxSearch::TaxSearch(SeqToKMers seqSplitter, int hits_max, bool best_only, double coverage, TaxConsensus* consensus_builder, std::string &kmer_index_path, std::string &tax_index_path):
    seq_splitter(seqSplitter),
    hits_max(hits_max),
    best_only(best_only),
    coverage(coverage),
    consensus_builder(consensus_builder),
    nodes(200000, NameNode("NA", -1, -2, 0)) //Expected size of RDP is around 200000
{
    readTaxIndex(tax_index_path);
    readKMerIndex(kmer_index_path);
    readTaxLevelNames();
}

void TaxSearch::readTaxIndex(std::string &file_path)
{
    ifstream input(file_path);
    if(!input.good())
        throw TaxSearchException("TaxSearch::readTaxIndex: File not found or readable");

    std::string line;
    while (std::getline(input, line))
    {
            //Typical format
        //#NODE_ID	PARENT_ID	LEVEL	NAME
        //0	-1	0	root
        //78163	0	1	K#Archaea
        //78164	78163	2	P#Crenarchaeota
        //78165	78164	3	C#Thermoprotei
        if(line[0]=='#') continue;

        vector<string> tokens = split(line, '\t');
        unsigned int node_id  = atoi(tokens[0].c_str());
        int parent_id         = atoi(tokens[1].c_str());
        int level             = atoi(tokens[2].c_str());
        string name           = tokens[3];

        NameNode node(name, level, parent_id, node_id);

        if(nodes.capacity()<=node_id)
            nodes.reserve(nodes.capacity()*2);

        nodes[node_id] = node;
    }

    input.close();
}

void TaxSearch::readKMerIndex(std::string &file_path)
{
    ifstream input(file_path);
    if(!input.good())
        throw TaxSearchException("TaxSearch::readKMerIndex: File not found or readable");

    int max_node_id = 0;
    std::string line;
    while (std::getline(input, line))
    {
        // #LEVEL	KMER	NODES
        // 0	0	0;
        // 0	1	0;
        // 0	2	0;
        // 1	0	1;2;
        // 1	1	1;
        // 1	2	1;2;4;
        if(line[0]=='#') continue;

        vector<string> tokens = split(line, '\t');
        unsigned int level = atoi(tokens[0].c_str());
        KMer kmer = stoul(tokens[1]);
        vector<string> nodeTokens = split(tokens[2],';');

        while(level_vector.size()<=level){
            level_vector.push_back(TaxLevel(seq_splitter.get_kmer_size()));
        }

        for(auto node_it = nodeTokens.begin(); node_it!=nodeTokens.end(); ++node_it){
            int node_id = atoi(node_it->c_str());
            level_vector[level].add_node_to_kmer(node_id, kmer);

            if(node_id>max_node_id) {
                max_node_id = node_id;
            }
        }
    }

    unsigned int node_counts_size = max_node_id+1;
    node_counts.resize(node_counts_size);

    input.close();
}

/**
 *
 * Debug function where second argument can be a literal "sequence".
 *
 * */
Hit TaxSearch::search(std::string &&seqName, std::string &&sequence){
    return search(seqName, sequence);
}

Hit TaxSearch::search(std::string &seqName, std::string &sequence)
{
//    int levels = level_vector.size()-1;
    vector< vector< string > > node_tax_table;

    vector<int> node_hits = searchNodes(sequence);

    for(auto hit_it = node_hits.begin(); hit_it!=node_hits.end(); ++hit_it){
        vector<string> node_tax_row;
        fill_node_tax_row(*hit_it, node_tax_row);

        node_tax_table.push_back(node_tax_row);
    }

    string consensus = consensus_builder->buildConsensus(node_tax_table);
    return make_tuple(seqName, consensus, node_hits.size());
}

void TaxSearch::fill_node_tax_row(int node_id, vector<string> &node_tax_row)
{
    NameNode &n = nodes[node_id];

    do{
        string name = n.getName();
        vector< string > words = split(name, '_');

        for(auto word_it = words.rbegin(); word_it!=words.rend(); ++word_it)
            node_tax_row.insert(node_tax_row.begin(), *word_it);

        n = nodes[n.getParentId()];
    }while(n.getParentId()>=0);
}

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
std::vector<int> TaxSearch::searchNodes(std::string &sequence)
{
    std::vector<int> ret;
    KMerSet kmer_set = seq_splitter.sequenceToKMers(sequence);

    for(auto level_it = level_vector.rbegin(); level_it!=level_vector.rend(); level_it++){
        std::fill(node_counts.begin(), node_counts.end(), 0); // Reset histogram.
        level_it->update_nodes_hist(node_counts, kmer_set);
        pickBestHits(ret, kmer_set.size());
        if(ret.size()>0)
            return ret;
    }

    return ret;
}

void TaxSearch::pickBestHits(std::vector<int> &ret, int kmer_size)
{
    vector< pair<int, int> > hits;
    int i = 0;

    for(auto node_it = node_counts.begin(); node_it!=node_counts.end(); ++node_it){
        if (*node_it > 0 && *node_it >= kmer_size * coverage){
            hits.push_back(pair<int, int>(i, *node_it));
        }

        ++i;
    }

    sort(hits.begin(), hits.end(), descendingPairSortOrder);

    if (best_only)
    {
        for(int i=0;i<hits_max && hits[i].second == hits[0].second;i++){
            ret.push_back(hits[i].first);  // TODO What if hits.size < hits_max ???
        }

        return;
    }

    for(int i=0;i<hits_max && i < hits.size();i++){
        ret.push_back(hits[i].first);
    }
}

void TaxSearch::readTaxLevelNames()
{
    unsigned int level = 0;
    int          pos   = 0;
    std::string level_name;

    for(auto node_it=nodes.begin(); node_it!=nodes.end(); ++node_it ){
        level      = node_it->getLevel();
        size_t pos = node_it->getName().find("#");
        if(pos==string::npos) continue;
        level_name = node_it->getName().substr(0, pos);  // "<string>#<...>"

        if (level >= level_names.size())
            level_names.resize(level + 1);

        level_names[level] = level_name;
    }
}

std::ostream & operator<<(std::ostream & os, Hit hit)
{
    os<<"Hit["<<std::get<0>(hit)<<", "<<std::get<1>(hit)<<", "<<std::get<2>(hit)<<"]";
    return os;
}
