#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "Common.h"
#include "TaxLevel.h"

using namespace std;

TaxLevel::TaxLevel(int k)
    //:kmer_to_node_vec((int) pow(4, k))
    :kmer_to_node_vec((int) pow(4, k))
{
}

void TaxLevel::update_nodes_hist(vector<unsigned int>&hist, KMerSet& kmer_set)
{
    for(auto kmer_it = kmer_set.begin(); kmer_it!=kmer_set.end(); ++kmer_it){

        list<int> &node_list = kmer_to_node_vec[*kmer_it];

        cerr << " KMER_VEC_SIZE: " << kmer_to_node_vec.size() << endl;
        cerr << " KMER: " << *kmer_it << endl;
        cerr << " NODE_LIST_SIZE " << node_list.size() << endl;

        for(auto node_it=node_list.begin(); node_it!=node_list.end(); ++node_it){
            cerr << "NODE: " << *node_it;
            cerr << " NODE_COUNTS_SIZE: " << hist.size();
            cerr << endl;

            if (*node_it >= hist.size())
                cerr << "HER2" << endl;

            hist[*node_it]++;
        }
    }
}

void TaxLevel::add_node_to_kmer(int node, KMer kmer)
{
    kmer_to_node_vec[kmer].push_back(node);
}
