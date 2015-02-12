#include "TaxNode.h"

TaxNode::TaxNode(TaxNode &parent, std::string &name, KMerSet &kmers, unsigned int node_id ):
    node_id(node_id)
{
}

TaxNode::TaxNode():
    node_id(0), name("root")
{
}

TaxNode& TaxNode::getParent()
{

}

std::string& TaxNode::getName()
{
}

KMerSet& TaxNode::getKMers()
{
}

std::vector<TaxNode*>& TaxNode::getChildren()
{

}
