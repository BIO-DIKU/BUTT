#include "Fasta.h"

#include <vector>

Fasta::Fasta(const std::string &filePath): inputStream(filePath.c_str(), std::ifstream::in)
{
    if(!inputStream){
        std::string msg("Fasta-file not found or not readable: "+filePath);
        throw FastaException(msg);
    }
}

FastaEntry Fasta::nextEntry()
{
    std::cout<<"nexxtEntry()"<<std::endl;
    bool lookingForHeader = nextHeader.empty();
    std::string header = nextHeader;
    std::string sequence;
    nextHeader = "";

    std::string line;
    while (std::getline(inputStream, line))
    {
        std::cout<<"Line read: "<<line<<std::endl;
        //line = line.substr(0,line.length()-1); 	// Strips newline
        if(line.length()==0) continue;			// Ignore empty lines

        if(lookingForHeader){
            if(line.at(0)=='>'){
                header = line.substr(1);
                lookingForHeader = false;
            }else{
                std::string msg("Bad fasta-format: Contents before first header. Line: \""+line+"\"");
                throw FastaException(msg);
            }
        }else{
            if(line.at(0)=='>'){
                nextHeader = line.substr(1);
                break;
            }

            sequence = sequence+line;
        }
    }

    std::cout<<"header: "<<header<<std::endl;
    std::cout<<"nextHeader: "<<nextHeader<<std::endl;
    std::cout<<"sequence: "<<sequence<<std::endl;


    if (sequence.empty()) {
        std::string msg("Bad fasta-format: Missing sequence for header \""+header+"\"");
        throw FastaException(msg);
    }

    FastaEntry ret;
    ret.header = header;
    ret.sequence = sequence;
    return ret;
}


bool Fasta::hasNextEntry()
{
    return inputStream.eof();
}
