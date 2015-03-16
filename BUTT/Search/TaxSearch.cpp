#include "TaxSearch.h"

#include "Common.h"

#include <fstream>
#include <string>

using namespace std;

TaxSearch::TaxSearch(SeqToKMers seqSplitter, int hits_max, bool best_only, double coverage):
    seq_splitter(seqSplitter),
    hits_max(hits_max),
    best_only(best_only),
    coverage(coverage),
    nodes(200000, NameNode("NA",-2,0)) //Expected size of RDP is around 200000
{

}


void TaxSearch::readTaxIndex(std::string &file_path)
{
    ifstream input(file_path);
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
        unsigned int node_id = atoi(tokens[0].c_str());
        int parent_id = atoi(tokens[1].c_str());
        string name = tokens[3];

        NameNode node(name, parent_id, node_id);

        if(nodes.capacity()<=node_id)
            nodes.reserve(nodes.capacity()*2);

        nodes[node_id] = node;
    }

    input.close();
}

void TaxSearch::readKMerIndex(std::string &file_path)
{
    ifstream input(file_path);
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

        for(auto node_it = nodeTokens.begin(); node_it!=nodeTokens.end(); node_it++){
            int node_id = atoi(node_it->c_str());
            kmer_node_indices[level][kmer].push_back(node_id);
        }
    }

    input.close();

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
std::set<int> TaxSearch::searchNodes(std::string sequence)
{
    KMerSet kmer_set = seq_splitter.sequenceToKMers(sequence);

}
