#include "SimpleTaxConsensus.h"

#include <map>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;
SimpleTaxConsensus::SimpleTaxConsensus()
{
}

std::string SimpleTaxConsensus::buildConsensus(std::vector< std::vector< std::string > > &tax_table)
{
    int rows = tax_table.size();
    if(rows==0) return "";

    string ret;

    int columns = tax_table[0].size();

    for(int col=0;col<columns;col++){
        map<string, int> col_occurences;
        for(int row=0;row<rows;row++){
            col_occurences[tax_table[row][col]]++;
        }

        vector< pair<string, int> > entryset;
        for(auto map_it = col_occurences.begin(); map_it!=col_occurences.end(); ++map_it){
            entryset.push_back(*map_it);
        }
        sort(entryset.begin(), entryset.end(), descendingSortOrderPair);

        ret+=entryset[0].first;
        if(col<columns-1)
            ret+=";";
    }

    return ret;
}
