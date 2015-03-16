#ifndef NAMENODE_H
#define NAMENODE_H

#include <string>

/**
 * @brief A node in a taxonomic tree specifying only node name, id and parent id.
 */
class NameNode
{
public:
    NameNode(std::string name, unsigned int parent, unsigned int node_id);
    NameNode(const NameNode& node);
    //NameNode();

    std::string &getName();

    unsigned int getParentId();

    unsigned int getNodeId();

private:
    std::string name;
    unsigned int parent, node_id;
};

#endif // NAMENODE_H
