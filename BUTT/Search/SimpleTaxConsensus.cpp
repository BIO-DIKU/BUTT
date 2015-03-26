#include "SimpleTaxConsensus.h"
#include <map>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

SimpleTaxConsensus::SimpleTaxConsensus(vector < string > _level_names)
{
    level_names = _level_names;
}

string SimpleTaxConsensus::buildConsensus(vector< vector< string > > &tax_table)
{
    int rows           = tax_table.size();
    int level          = 0;
    int min_row_length = 999999;
    string ret;

    if(rows==0) return "";

    for(int row=0;row<rows;++row){
        if (tax_table[row].size() < min_row_length)
            min_row_length = tax_table[row].size();
    }

    for(int col=0;col<min_row_length;++col){
        if (columnPerfectConsensus(tax_table, col)) {
            if (tax_table[0][col][1] == '#') {
                if (level > 0)
                    ret+=";";

                level++;
            }
            else
                ret+="_";

            ret+=tax_table[0][col];
        } else {    
            break;
        }
    }

    return ret+buildTaxSuffix(level);
}

bool SimpleTaxConsensus::columnPerfectConsensus(vector< vector< string > > &tax_table, int col)
{
    for(int row=1;row<tax_table.size();row++){
        if (tax_table[row][col] != tax_table[0][col])
            return false;
    }

    return true;
}

string SimpleTaxConsensus::buildTaxSuffix(int level)
{
    string suffix = "";

    for(int i=level;i < level_names.size(); ++i){
        if (i > 0)
            suffix += ";";
        suffix += level_names[i] + "#";
    }

    return suffix;
}

//      string msg("Something bad happened. Taxonomy consensus: \""+ret+"\", Taxonomy level: \""+to_string(level)+"\"");
//      throw SimpleTaxConsensusException(msg);
