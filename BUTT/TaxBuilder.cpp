#include "TaxBuilder.h"

#include <vector>
#include <string>

#include "Common.h"

TaxBuilder::TaxBuilder(SeqToKMers seqSplitter):
    sequenceSplitter(seqSplitter),
    root(new TaxNode())
{
}

TaxBuilder::~TaxBuilder()
{
    delete root;
}

void TaxBuilder::addTaxEntry(std::string taxonomyString, std::string sequence)
{
    std::vector<std::string> tax_tokens;
    bool tax_string_status = checkTaxEntry(taxonomyString, tax_tokens);

    if(!tax_string_status) throw TaxonomyStringException("Taxonomy string not valid: "+taxonomyString);

    TaxNode* node = &root;


}


bool TaxBuilder::checkTaxEntry(std::string &taxonomyString, std::vector<std::string> &splitTaxString)
{
    split(taxonomyString, ";", splitTaxString);

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

}

unsigned int TaxBuilder::treeSize()
{

    return 0;
}
