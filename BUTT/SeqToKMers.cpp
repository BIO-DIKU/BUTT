#include "SeqToKMers.h"

#include <climits>
#include <iostream>

SeqToKMers::SeqToKMers(unsigned int kmer_size, unsigned int step_size):
    kmer_size(kmer_size),
    step_size(step_size)
{
    // The number of bits in an int is sizeof(int)*CHAR_BIT.
    // As we use 2 bits for each nucleotide, an exception is thrown if kmer_size>(bits in int)/2
    unsigned int maxSize = (sizeof(int)*CHAR_BIT)/2;
    if(kmer_size>maxSize)
    {
        std::string msg = "K-mer size too large "+std::to_string(kmer_size)+" (max-size: "+std::to_string(maxSize)+")";
        throw SeqToKMerException(msg);
    }else if(kmer_size==0)
    {
        std::string msg = "K-mer size 0 not allowed";
        throw SeqToKMerException(msg);
    }

    if(step_size==0)
    {
        std::string msg = "Step size 0 not allowed";
        throw SeqToKMerException(msg);
    }
}

int decode(char nucl){
   switch(std::toupper(nucl)){
   case 'A': return NUCL_A;
   case 'C': return NUCL_C;
   case 'G': return NUCL_G;
   case 'U': return NUCL_U;
   case 'T': return NUCL_T;
   default: return -1;
   }
}

KMerSet SeqToKMers::sequenceToKMers(std::string &sequence)
{
    KMerSet ret;
    unsigned int mask = (1<<(kmer_size*2))-1;
    int n = sequence.length();
    KMer tmp = 0;
    int delta = std::min(kmer_size, step_size);
    for(int pos = 0; pos<=(n-(int)kmer_size); pos+=step_size)
    {
        tmp <<= 2*step_size;
        tmp &= mask;

        for(unsigned int i=0; i<(pos==0?kmer_size:delta); i++){
            char nucl = sequence[ pos+kmer_size-i-1 ];
            int dec = decode(nucl);
            if(dec<0){}
            tmp |= (dec<<(2*i));
        }

        ret.insert(tmp);

    }

    return ret;
}
