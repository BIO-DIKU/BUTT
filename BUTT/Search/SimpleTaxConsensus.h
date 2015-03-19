#ifndef SIMPLETAXCONSENSUS_H
#define SIMPLETAXCONSENSUS_H

#include "TaxConsensus.h"

class SimpleTaxConsensus: public TaxConsensus
{
public:
    SimpleTaxConsensus();

    std::string buildConsensus(std::vector< std::vector< std::string > > &tax_table);

    static bool descendingSortOrderPair(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
        return a.second>b.second;
    }

};

#endif // SIMPLETAXCONSENSUS_H
