#ifndef TAXCONSENSUS_H
#define TAXCONSENSUS_H

#include <vector>
#include <string>

class TaxConsensus
{
public:
    virtual std::string buildConsensus(std::vector< std::vector< std::string > > &tax_table) = 0;
};

#endif // TAXCONSENSUS_H
