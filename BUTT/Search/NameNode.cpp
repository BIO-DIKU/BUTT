#include "NameNode.h"

NameNode::NameNode(std::string name, unsigned int parent, unsigned int node_id):
    name(name),
    parent(parent),
    node_id(node_id)
{
}

NameNode::NameNode(const NameNode& node):
    name(node.name),
    parent(node.parent),
    node_id(node.node_id)
{

}

//NameNode::NameNode():
//    name("NA"),
//    parent(-2),
//    node_id(0)
//{
//
//}
