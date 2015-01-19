#ifndef TAXBUILDER_H
#define TAXBUILDER_H

#include <string>
#include <SeqToKMers>

/**
 * @brief The TaxBuilder class
 * Class for building the databases for the taxonomy classifier. After construction a
 * set of fasta entries can be added and as a final step the databases can be generated
 * with the saveDatabases function. Only entries added before a call to saveDatabases
 * are stored.
 */
class TaxBuilder
{
public:
    /**
     * @brief TaxBuilder
     * Prepare the taxonomy builder. No real action is taken here.
     * @param seqSplitter
     */
    TaxBuilder(SeqToKMers seqSplitter);

    /**
     * @brief addFastaEntry
     * @param taxonomyString
     * @param sequence
     */
    void addFastaEntry(string taxonomyString, string sequence);

    void saveDatabases(string directory, string prefix);
private:

    SeqToKMers sequenceSplitter;

    void buildDatabases();
    void treeRemap();
    void pullUnions(TaxNode &n);
};

#endif // TAXBUILDER_H
