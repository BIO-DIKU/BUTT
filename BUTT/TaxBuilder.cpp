#include "TaxBuilder.h"

#include <vector>
#include <string>
#include <iostream>

#include "Common.h"

TaxBuilder::TaxBuilder(SeqToKMers seqSplitter):
    sequenceSplitter(seqSplitter),
    root(new TaxNode()),
    tree_size(1)
{
}

TaxBuilder::~TaxBuilder()
{
    delete root;
}

void TaxBuilder::addTaxEntry(std::string &&taxonomyString, std::string &&sequence)
{
    std::vector<std::string> tax_tokens;
    bool tax_string_status = checkTaxEntry(taxonomyString, tax_tokens);

    if(!tax_string_status) {
        std::string msg = "Taxonomy string not valid: "+taxonomyString;
        throw TaxonomyStringException(msg);
    }

    TaxNode* node = root;

    for(unsigned int t=0;t<tax_tokens.size();t++)
    {
        TaxNode* next_child = node->getChild(tax_tokens[t]);
        if(next_child==NULL)
            next_child = new TaxNode(node, tax_tokens[t], tree_size++);

        if(isLeaf(tax_tokens, t)){
            next_child->addKMers(sequenceSplitter.sequenceToKMers(sequence));
            break;
        }else{
            node = next_child;
        }
    }

}

bool TaxBuilder::isLeaf(std::vector<std::string> &tax_path, unsigned int t)
{
    return (t+1>=tax_path.size() || tax_path[t+1].length()==2); // leaf if tax_path[t+1] has format "C#"
}

bool TaxBuilder::checkTaxEntry(std::string &taxonomyString, std::vector<std::string> &splitTaxString)
{
    split(taxonomyString, ';', splitTaxString);

    if(level_names.empty()){ // If this is the first taxonomyString that is checked, fill up level_names
        for(int i=0;i<splitTaxString.size();i++){
            if(splitTaxString[i].length()<2 || splitTaxString[i][1]!='#') return false; //Check criteria 1
            if(i<splitTaxString.size()-1 && splitTaxString[i].length()==2 && splitTaxString[i+1].length()>2)
                return false; //Check criteria 3

            char level_name = splitTaxString[i][0];

            if(std::find(level_names.begin(), level_names.end(), level_name)!=level_names.end())
                return false; // Check criteria 2

            level_names.push_back(level_name);
        }

    }else{ // Any taxonomyString but the first have to match the first

        if(splitTaxString.size()!=level_names.size()) return false; //Check criteria 4

        for(int i=0;i<splitTaxString.size();i++){
            if(splitTaxString[i].length()<2 || splitTaxString[i][1]!='#') return false; //Check criteria 1
            if(i<splitTaxString.size()-1 && splitTaxString[i].length()==2 && splitTaxString[i+1].length()>2)
                return false; //Check criteria 3

            char level_name = splitTaxString[i][0];

            if(level_names[i]!=level_name) return false; //Check criteria 4 and implicitly also 2
        }

    }

    return true;
}

TaxNode& TaxBuilder::getNode(unsigned int id)
{
    TaxNode* n = root->findNode(id);
    return *n;
}

unsigned int TaxBuilder::treeSize()
{
    return tree_size;
}

void TaxBuilder::pullUnions(TaxNode &n)
{
    if(n.children.size()==0)
        return;

    for(auto child_it=n.children.begin(); child_it!=n.children.end(); child_it++){
        pullUnions( *(child_it->second) );
    }

    for(auto child_it=n.children.begin(); child_it!=n.children.end(); child_it++){
        n.addKMers(child_it->second->kmers);
    }
}

void TaxBuilder::saveIndex(std::string directory, std::string prefix)
{

}
