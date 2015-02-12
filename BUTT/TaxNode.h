#ifndef TAXNODE_H
#define TAXNODE_H

#include <string>
#include <vector>

#include "Common.h"

/**
 * @brief The TaxNode class
 * A node in a taxonomic tree. Holds and provides access to parent and children-pointers,
 * a set of K-mers associated with this node and a node id.
 */
class TaxNode
{
public:
    const unsigned int node_id; ///< Node id

    /**
     * @brief TaxNode constructor.
     * Store constructor arguments and add itself to parents child list.
     */
    TaxNode(TaxNode &parent, std::string &name, KMerSet &kmers, unsigned int node_id );

    /** Access parent node */
    TaxNode &getParent();

    /** Access name */
    std::string &getName();

    /** Access k-mer set */
    KMerSet &getKMers();

    /** Access child nodes */
    std::vector<TaxNode*> &getChildren();

private:
    TaxNode* parent;
    std::map<std::string, TaxNode*> children;
    const std::string name;

    // Constructor for root node
    TaxNode();

    friend class TaxBuilder;

};

#endif // TAXNODE_H
