/* Copyright 2015 BIO-DIKU */

#ifndef BUTT_INDEX_TAXNODE_H_
#define BUTT_INDEX_TAXNODE_H_

#include <string>
#include <vector>
#include <map>

#include "Common.h"

/**
 * @brief The TaxNode class
 * A node in a taxonomic tree. Holds and provides access to parent and
 * children-pointers, a set of K-mers associated with this node and a node id.
 */
class TaxNode {
 public:
    const unsigned int node_id;   ///< Node id

    /**
     * @brief TaxNode constructor.
     * Store constructor arguments and add itself to parents child list.
     */
    TaxNode(TaxNode *parent, std::string &name, unsigned int node_id);

    /** Access parent node */
    TaxNode &getParent();

    /** Access name */
    const std::string &getName();

    /** Access k-mer set */
    KMerSet &getKMers();

    /** Add k-mer set */
    void addKMers(KMerSet &&kmers_);

    /** Add k-mer set */
    void addKMers(KMerSet &kmers_);

    /** Access child nodes */
    // std::vector<TaxNode*> &getChildren();
    TaxNode* getChild(std::string &child_name);

 private:
    TaxNode* parent;
    std::map<std::string, TaxNode*> children;
    const std::string name;
    KMerSet kmers;

    // Constructor for root node
    TaxNode();

    friend class TaxBuilder;
    TaxNode* findNode(int id);
};

#endif   // BUTT_INDEX_TAXNODE_H_
