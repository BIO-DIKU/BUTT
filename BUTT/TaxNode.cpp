#include "TaxNode.h"

TaxNode::TaxNode(TaxNode *parent, std::string &name, unsigned int node_id ):
    node_id(node_id),
    parent(parent),
    name(name)
{
    parent->children[name] = this;
}

TaxNode::TaxNode():
    node_id(0), name("root")
{
}

TaxNode& TaxNode::getParent()
{
    return *parent;
}

const std::string& TaxNode::getName()
{
    return name;
}

KMerSet& TaxNode::getKMers()
{
    return kmers;
}

void TaxNode::addKMers(KMerSet &kmers_)
{
    for(auto it = kmers_.begin(); it!=kmers_.end();it++){
        kmers.insert(*it);
    }
}

void TaxNode::addKMers(KMerSet &&kmers_)
{
    for(auto it = kmers_.begin(); it!=kmers_.end();it++){
        kmers.insert(*it);
    }
}

TaxNode* TaxNode::getChild(std::string &child_name)
{
    auto child_it = children.find(child_name);
    if(child_it==children.end()) return NULL;
    return child_it->second;
}

TaxNode* TaxNode::findNode(int id)
{
    if(node_id==id) return this;
    for(auto it = children.begin(); it!=children.end(); it++){
        TaxNode* node = it->second->findNode(id);
        if(node!=NULL) return node;
    }
    return NULL;
}
