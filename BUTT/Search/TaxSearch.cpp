#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "TaxSearch.h"
#include "Common.h"

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
        //#LEVEL	KMER	NODES
        //0	0	0;
        //0	1	0;
        //0	2	0;
        //1	0	1;2;
        //1	1	1;
        //1	2	1;2;4;
        if(line[0]=='#') continue;

        vector<string> tokens = split(line, '\t');
        unsigned int level = atoi(tokens[0].c_str());
        KMer kmer = stoul(tokens[1]);
        vector<string> nodeTokens = split(tokens[2],';');

        while(kmer_node_indices.size()<=level){
            kmer_node_indices.push_back( vector< list<int> >() );
        }

        while(kmer_node_indices[level].size()<=kmer){
            kmer_node_indices[level].push_back( list<int>() );
        }

        for(auto node_it = nodeTokens.begin(); node_it!=nodeTokens.end(); ++node_it){
            int node_id = atoi(node_it->c_str());
            kmer_node_indices[level][kmer].push_back(node_id);

            if(node_id>max_node_id)
                max_node_id = node_id;
        }
    }

    unsigned int node_counts_size = max_node_id+1;
    node_counts.resize(node_counts_size);

    input.close();

}

Hit TaxSearch::search(std::string &&seqName, std::string &&sequence){
    return search(seqName, sequence);
}

Hit TaxSearch::search(std::string &seqName, std::string &sequence)
{
    set<int> node_hits = searchNodes(sequence);

    int levels = kmer_node_indices.size()-1;
    vector< vector< string > > node_tax_table;

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

        for(auto word_it = words.rbegin(); word_it!=words.rend(); ++word_it){
            node_tax_row.insert(node_tax_row.begin(), *word_it);
        }

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
std::set<int> TaxSearch::searchNodes(std::string &sequence)
{
    KMerSet kmer_set = seq_splitter.sequenceToKMers(sequence);

    std::fill(node_counts.begin(), node_counts.end(), 0);

    for(int level=kmer_node_indices.size()-1; level>0; level--){
        for(auto kmer_it = kmer_set.begin(); kmer_it!=kmer_set.end(); ++kmer_it){

            list<int> &node_list = kmer_node_indices[level][*kmer_it];

            cerr << "LEVEL: " << to_string(level) << endl;
            cerr << " KMER: " << *kmer_it << endl;
            cerr << " NODE_LIST_SIZE " << node_list.size() << endl;

            for(auto node_it=node_list.begin(); node_it!=node_list.end(); ++node_it){
                cerr << "NODE: " << *node_it;
                cerr << " NODE_COUNTS_SIZE: " << node_counts.size();
                cerr << endl;

                if (*node_it >= node_counts.size())
                    cerr << "HER2" << endl;

                node_counts[*node_it]++;
            }
        }
        std::set<int> ret;
        pickBestHits(ret, kmer_set.size());
        if(ret.size()>0)
            return ret;
    }

    std::set<int> ret;
    return ret;
}

void TaxSearch::pickBestHits(std::set<int> &ret, int kmer_size)
{
    vector< pair<int, int> > hits;
    int i = 0;

    for(auto node_it = node_counts.begin(); node_it!=node_counts.end(); ++node_it){
        if (*node_it >= kmer_size * coverage) {
            hits.push_back(pair<int, int>(i, *node_it));
        }

        ++i;
    }

    sort(hits.begin(), hits.end(), descendingPairSortOrder);

    for(int i=0;i<hits_max;i++){
        ret.insert(hits[i].first);
    }
}

void TaxSearch::readTaxLevelNames()
{
    int         level = 0;
    int         pos   = 0;
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
