#include "NameNode.h"

NameNode::NameNode(std::string name, int level, int parent, unsigned int node_id):
    name(name),
    level(level),
    parent(parent),
    node_id(node_id)
{
}

NameNode::NameNode(const NameNode& node):
    name(node.name),
    level(node.level),
    parent(node.parent),
    node_id(node.node_id)
{
}

std::string &NameNode::getName(){ return name; }
int NameNode::getLevel(){ return level; }
int NameNode::getParentId(){ return parent; }
unsigned int NameNode::getNodeId(){ return node_id; }
