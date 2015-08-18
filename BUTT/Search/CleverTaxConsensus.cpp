/* Copyright 2015 BIO-DIKU */

#include "Search/CleverTaxConsensus.h"

#include <limits>
#include <map>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>
#include <utility>
// #include <iostream>   // TODO(martin): for debugging - remove

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

string CleverTaxConsensus::buildConsensus(vector< vector< string > > &tax_table, float consensus_min) {
    int          rows           = tax_table.size();
    int          level          = 0;
    string       ret            = "";
    unsigned int min_row_length = 0;

    if (rows == 0) return ret;

    min_row_length = minRowLength(tax_table, rows);

    for (unsigned int col = 0; col < min_row_length; ++col) {
        columnConsensus(tax_table, col);
        // if (columnConsensus(tax_table, col)) {
        //     if (tax_table[0][col][1] == '#') {
        //         if (level > 0) {
        //             ret+=";";
        //         }
        //
        //         level++;
        //     } else {
        //         ret += "_";
        //     }
        //
        //     ret += tax_table[0][col];
        // } else {
        //     break;
        // }
    }

    // std::cerr << "HEEEEEEEEEEER: " << ret << std::endl;
    // => K#a_1;P#b_1;C#c_n1

    return ret + buildTaxSuffix(level);
}

pair<string, float> CleverTaxConsensus::columnConsensus(vector< vector< string > > &tax_table, int col) {
    map<string, int> frequencies;
    string           word;
    int              count;
    string           max_word;
    int              max_count = 0;
    int              rows      = tax_table.size();

    for (int row = 0; row < rows; row++) {
      word    = tax_table[row][col];
      auto it = frequencies.find(word);

      if (it == frequencies.end()) {
        frequencies[word] = 0;
      } else {
        count             = it->second;
        frequencies[word] = count + 1;

        if (count + 1 > max_count) {
          max_word  = word;
          max_count = count;
        }
      }
    }

    return pair<string, float>(max_word, max_count / rows);
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
