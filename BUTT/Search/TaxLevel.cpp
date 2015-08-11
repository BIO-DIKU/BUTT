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
    :kmer_to_node_vec((int) pow(4, k))
{
}

void TaxLevel::update_nodes_hist(vector<unsigned int>&hist, KMerSet& kmer_set)
{
    for(auto kmer_it = kmer_set.begin(); kmer_it!=kmer_set.end(); ++kmer_it){
        list<int> &node_list = kmer_to_node_vec[*kmer_it];

        for(auto node_it=node_list.begin(); node_it!=node_list.end(); ++node_it)
            hist[*node_it]++;
    }
}

void TaxLevel::add_node_to_kmer(int node, KMer kmer)
{
    kmer_to_node_vec[kmer].push_back(node);
}
