#include <iostream>
#include <string>

#include "Tests/TestAll.h"
#include "Fasta.h"
#include "TaxBuilder.h"

using namespace std;

void benchmarkBuilder(int argc, char** argv);

int main(int argc, char** argv)
{
    TestAll tests;
    tests.runTests();

    //benchmarkBuilder(argc, argv);

    return 0;
}


void benchmarkBuilder(int argc, char** argv)
{
    cout<<"Assuming second argument is a fasta file"<<endl;

    Fasta fasta(argv[1]);
    TaxBuilder builder(SeqToKMers(9, 1));

    while(fasta.hasNextEntry()){
        FastaEntry entry = fasta.nextEntry();

        string taxString = entry.header.substr( entry.header.find(' ')+1 );
        builder.addTaxEntry( taxString, entry.sequence );
    }

    string kmerFile("kmerIndex.txt");
    builder.saveKMerIndex(kmerFile);

    string taxFile("taxIndex.txt");
    builder.saveTaxIndex(taxFile);

}
