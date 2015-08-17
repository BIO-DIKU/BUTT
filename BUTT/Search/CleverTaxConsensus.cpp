/* Copyright 2015 BIO-DIKU */

#include "Search/CleverTaxConsensus.h"

#include <limits>
#include <map>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>
#include <iostream>   // TODO(martin): for debugging - remove

using namespace std;

CleverTaxConsensus::CleverTaxConsensus(vector < string > _level_names) {
    level_names = _level_names;
}

unsigned int CleverTaxConsensus::minRowLength(vector< vector< string > > &tax_table, int rows) {
    unsigned int min_row_length = std::numeric_limits<unsigned int>::max();;

    for (int row = 0; row < rows; ++row) {
        if (tax_table[row].size() < min_row_length) {
            min_row_length = tax_table[row].size();
        }
    }

    return min_row_length;
}

string CleverTaxConsensus::buildConsensus(vector< vector< string > > &tax_table) {
    int          rows           = tax_table.size();
    int          level          = 0;
    string       ret            = "";
    unsigned int min_row_length = 0;

    if (rows == 0) return ret;

    min_row_length = minRowLength(tax_table, rows);

    for (unsigned int col = 0; col < min_row_length; ++col) {
        if (columnPerfectConsensus(tax_table, col)) {
            if (tax_table[0][col][1] == '#') {
                if (level > 0) {
                    ret+=";";
                }

                level++;
            } else {
                ret += "_";
            }

            ret += tax_table[0][col];
        } else {
            break;
        }
    }

    // std::cerr << "HEEEEEEEEEEER: " << ret << std::endl;
    // => K#a_1;P#b_1;C#c_n1

    return ret + buildTaxSuffix(level);
}

bool CleverTaxConsensus::columnPerfectConsensus(vector< vector< string > > &tax_table, int col) {
    for (unsigned int row = 1; row < tax_table.size(); row++) {
        if (tax_table[row][col] != tax_table[0][col]) {
            return false;
        }
    }

    return true;
}

string CleverTaxConsensus::buildTaxSuffix(int level) {
    string suffix = "";

    for (unsigned int i = level; i < level_names.size(); ++i) {
        if (i > 0) {
            suffix += ";";
        }

        suffix += level_names[i] + "#";
    }

    return suffix;
}

//      string msg("Something bad happened. Taxonomy consensus: \""+ret+"\", Taxonomy level: \""+to_string(level)+"\"");
//      throw CleverTaxConsensusException(msg);
