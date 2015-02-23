#ifndef TAXBUILDER_H
#define TAXBUILDER_H

#include <string>
#include <list>
#include <fstream>

#include "SeqToKMers.h"
#include "TaxNode.h"


/**
 * @brief Exception thrown by TaxBuilder class
 */
class TaxonomyStringException: public std::exception {
public:
    TaxonomyStringException(std::string &msg): exceptionMsg(msg){}
    TaxonomyStringException(const TaxonomyStringException &e): exceptionMsg(e.exceptionMsg){}
    const std::string exceptionMsg;
};


/**
 * @brief The TaxBuilder class
 * Class for building the index for the taxonomy classifier. After construction a
 * set of fasta entries can be added and as a final step the index can be generated
 * with the saveIndex function. Only entries added before a call to saveIndex
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

    ~TaxBuilder();

    /**
     * @brief Add a taxonomy entry specified by a taxonomy string and a sequence to the
     * taxonomy classifier.
     * A TaxonomyStringException is thrown if the taxonomy string is malformated.
     * @param taxonomyString A taxonomy string of the format "[<C>#<Name>;<C>#<Name>;..]"
     * where <C> is a classification character indicating the level of the classification
     * and <Name> is the classification itself. An example of a valid taxonomy string could be:
     * "K#Bacteria;P#Proteobacteria;C#Gammaproteobacteria;O#Vibrionales;F#Vibrionaceae;G#Vibrio;S#Vibrio"
     * @param sequence An RNA/DNA sequence associated with this taxonomy.
     */
    void addTaxEntry(std::string &&taxonomyString, std::string &&sequence);


    /**
     * @brief Build and save taxonomy index.
     */
    void saveTaxIndex(std::string &file_path);

    /**
     * @brief Build and save kmer index.
     */
    void saveKMerIndex(std::string &file_path);

    /**
     * @brief Return the node given an id.
     * Throws a MissingNodeException if unknown id.
     * This function is provided only for debugging and testing purposes.
     */
    TaxNode& getNode(unsigned int id);

    /**
     * @brief Return the number of nodes in the tree
     * This function is provided only for debugging and testing purposes.
     */
    unsigned int treeSize();
private:

    const SeqToKMers sequenceSplitter;

    TaxNode* root;
    unsigned int tree_size;

    void buildIndex();

    inline bool isLeaf(std::vector<std::string> &tax_path, unsigned int t);

    /**
     * @brief checkTaxEntry checks if the taxonomyString satisfies:
     * 1: The format must be C#Name;C#Name;...C#Name where C can be any single character and Name is a (possibly empty) string without '#'
     * 2: Each level has its own distinct character
     * 3: If a level has an empty name all following names must be empty
     * 4: The number and order of level names is the same as for any previous checked entry
     * @param taxonomyString will be filled with the taxonomyString split by ';' for efficiency
     * @return true iff the taxonomyString satisfies the above criteria
     */
    bool checkTaxEntry(std::string &taxonomyString, std::vector<std::string> &splitTaxString);

    std::vector<char> level_names;

    friend class TestTaxBuilder;

    /**
     * When fasta entries are added their k-mers are only added to the bottom node in
     * their classification. This function pulls all k-mers into parent-nodes using unions.
     */
    void pullUnions(TaxNode &n);

    void saveTaxIndex(TaxNode* n, int depth, std::ofstream &ostream);
    void buildKMerIndex(TaxNode* n, int depth, std::vector< std::map< KMer, std::list<int> > > &kmer_index);
};

#endif // TAXBUILDER_H
