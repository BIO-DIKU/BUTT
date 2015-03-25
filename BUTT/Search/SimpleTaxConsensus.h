#ifndef SIMPLETAXCONSENSUS_H
#define SIMPLETAXCONSENSUS_H

#include "TaxConsensus.h"

/**
 * @brief Exception thrown by SimpleTaxConsensus class
 */
class SimpleTaxConsensusException: public std::exception {
public:
    SimpleTaxConsensusException(std::string &msg): exceptionMsg(msg){}
    SimpleTaxConsensusException(const SimpleTaxConsensusException &e): exceptionMsg(e.exceptionMsg){}
    const std::string exceptionMsg;
};


class SimpleTaxConsensus: public TaxConsensus
{
public:
    SimpleTaxConsensus();

    /**
     * Function for building a consensus string from a given taxonomy table.
     * The consensus string terminates at the last common ancestor. If mulitple
     * words are present separated by _ at any taxonomy level these are matched
     * individually.
     *
     * tax_table - A taxonomy table given as a vector of vectors of strings.
     *
     * Examples
     *
     *     buildConsensus({{"K#a_1", "P#b_1", "C#c_1"}, {"K#a_1","P#b_2","C#x_1"}})
     *       // => "K#a_1;P#b;C#;O#;F#;G#;S#"
     *
     * Returns a string.
     */
    std::string buildConsensus(std::vector< std::vector< std::string > > &tax_table);

    /**
     * Sort function for sorting pairs in decending order according to the
     * .second member which is an int.
     *
     * a - pair where .first is a std::string and .second is an int.
     * b - pair where .first is a std::string and .second is an int.
     *
     * Returns bool.
     */
    static bool descendingSortOrderPair(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
        return a.second>b.second;
    }
};

#endif // SIMPLETAXCONSENSUS_H
