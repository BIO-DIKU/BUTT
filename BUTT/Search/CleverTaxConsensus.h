/* Copyright 2015 BIO-DIKU */

#ifndef BUTT_SEARCH_CLEVERTAXCONSENSUS_H_
#define BUTT_SEARCH_CLEVERTAXCONSENSUS_H_

#include "utility"
#include "string"
#include "vector"
#include "TaxConsensus.h"

/**
 * @brief Exception thrown by CleverTaxConsensus class
 */
class CleverTaxConsensusException: public std::exception {
 public:
    CleverTaxConsensusException(std::string &msg): exceptionMsg(msg) {}
    CleverTaxConsensusException(const CleverTaxConsensusException &e):
        exceptionMsg(e.exceptionMsg) {}

    const std::string exceptionMsg;
};

class CleverTaxConsensus: public TaxConsensus {
 public:
    CleverTaxConsensus(std::vector <std::string> level_names);

    /**
     * Function for building a consensus string from a given taxonomy table.
     * The consensus string terminates at the last common ancestor with a
     * consensus above the specified threadhold. If mulitple words are present
     * separated by _ at any taxonomy level these are matched individually.
     *
     * @param  tax_table  A taxonomy table given as a vector of vectors of
     *                    strings.
     * @param  consensus  Minimum consensus.
     *
     * @example
     *
     *     buildConsensus({{"K#a_1", "P#b_1", "C#c_1"},
     *                     {"K#a_1", "P#b_1", "C#x_1"},
     *                     {"K#a_1", "P#b_2", "C#z_1"}}, 0.5)
     *       // => "K#a_1(100/100);P#b_1(100/66);C#;O#;F#;G#;S#"
     *       // Because consensus at the first word on class (C) level is 0.33
     *       // and hence below the consensus threadhold it is not included.
     *
     * @return  A consensus string.
     */
    std::string buildConsensus(std::vector< std::vector< std::string > > &tax_table, float consensus_min);

 private:

   /**
    * Determines the minimum row length.
    *
    * @param tax_table A taxonomy table.
    * @param rows      Number of rows in table.
    *
    * @return Minimum row length.
    */
    unsigned int minRowLength(std::vector< std::vector< std::string > > &tax_table, int rows);

    std::vector< std::string > level_names;

    std::string buildTaxSuffix(int level);

    /**
     * For all rows in a given column of a given tax_table find the most
     * frequent word and return a pair with this word and the percent frequency
     * it was found.
     *
     * @param  tax_table  Taxonomy table.
     * @param  col        Column number.
     * @return            Pair with most frequent word and percent.
     */
    std::pair<std::string, float> columnConsensus(std::vector< std::vector< std::string > > &tax_table, int col);
};

#endif   // BUTT_SEARCH_SIMPLETAXCONSENSUS_H_
