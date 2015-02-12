#include "SeqToKMers.h"

#include <climits>
#include <iostream>
#include <cmath>

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

unsigned int SeqToKMers::decodeKMer(std::string &sequence, unsigned int pos, KMer &buffer, int suffixSz)
{
    for(int i=0; i<suffixSz; i++){
        char nuclChar = sequence[ pos+kmer_size-i-1 ];
        int nucl = decode(nuclChar);
        if(nucl<0) return pos+kmer_size-i;
        buffer |= (nucl<<(2*i));
    }
    return 0;
}

KMerSet SeqToKMers::sequenceToKMers(std::string &sequence)
{
    KMerSet ret;
    unsigned int mask = (1<<(kmer_size*2))-1;
    KMer buffer = 0;

    int status = 0;
    int suffix_size = kmer_size;
    int stepBy = step_size;
    int minMultiple = 1; // The smallest multiple of step_size larger than last status (or 1 if status=0)

    for( int pos=0; pos<=((int)sequence.length()-(int)kmer_size); pos+=stepBy ){

        status = decodeKMer(sequence, pos, buffer, suffix_size );

        if(status==0){  // Complete k-mer was stored in buffer.
            ret.insert(buffer);

            suffix_size = std::min(kmer_size,step_size);
            minMultiple = 1;
        }else{  // An unknown nucleotide was encountered. Fast forward window
            suffix_size = status;
            minMultiple = (int)std::ceil(status/step_size);
        }

        // Proceed to next window
        stepBy = minMultiple*step_size;
        buffer <<= 2*stepBy;
        buffer &= mask;
    }

    return ret;
}
