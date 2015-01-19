#ifndef TAXBUILDER_H
#define TAXBUILDER_H

#include <string>

#include "SeqToKMers.h"
#include "TaxNode.h"

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
     * @brief Add a fasta entry specified by a taxonomy string and a sequence to the
     * taxonomy classifier.
     * @param taxonomyString A taxonomy string of the format "[<C>#<Name>;<C>#<Name>;..]"
     * where <C> is a classification character indicating the level of the classification
     * and <Name> is the classification itself. An example of a valid taxonomy string could be:
     * "K#Bacteria;P#Proteobacteria;C#Gammaproteobacteria;O#Vibrionales;F#Vibrionaceae;G#Vibrio;S#Vibrio"
     * @param sequence An RNA/DNA sequence associated with this taxonomy.
     */
    void addFastaEntry(std::string taxonomyString, std::string sequence);

    /**
     * @brief Build and save database.
     */
    void saveDatabases(std::string directory, std::string prefix);

private:

    SeqToKMers sequenceSplitter;

    void buildDatabases();

    void treeRemap();

    /**
     * When fasta entries are added their k-mers are only added to the bottom node in
     * their classification. This function pulls all k-mers into parent-nodes using unions.
     */
    void pullUnions(TaxNode &n);
};

#endif // TAXBUILDER_H
