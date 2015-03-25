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
    int rows  = tax_table.size();
    int level = 3; // FIXME

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

    switch (level) {
    case 0:
      return ret+";K#;P#;C#;O#;F#;G#;S#";
    case 1:
      return ret+";P#;C#;O#;F#;G#;S#";
    case 2:
      return ret+";C#;O#;F#;G#;S#";
    case 3:
      return ret+";O#;F#;G#;S#";
    case 4:
      return ret+";F#;G#;S#";
    case 5:
      return ret+";G#;S#";
    case 6:
      return ret+";S#";
    default:
      std::string msg("Something bad happened. Taxonomy consensus: \""+ret+"\", Taxonomy level: \""+to_string(level)+"\"");
      throw SimpleTaxConsensusException(msg);
    }
}
