#ifndef C_GOL_H
#define C_GOL_H

#include <exception>
#include "GOL.h"

class too_few_bits_exception: public std::exception {
    virtual const char* what() const throw() {
        return "Requested more random bits than the system can supply in one go";
    }
};

class C_GOL: public GOL {

    protected:
    BitBoard seed_map;
    unsigned int seed;
    
    BitBoard create_seed_map(unsigned int seed);

    public:
    C_GOL(int sx, int sy,unsigned int seed_);
    
    C_GOL();
    
    unsigned int get_seed();
    
    void apply_xormap(BitBoard &map);
    
    template<int len> std::bitset<len> rand_bits() {
        if (len > std::max(sizex, sizey)) {throw too_few_bits_exception();}
        const static int multipliers[5] = {7,11,13,17,19};
        std::bitset<len> ret;
        const int shift = seed % sizex*sizey;
        const int multi = multipliers[seed%5];
        for (int i = 0; i < len; ++i) {
            ret[i] = board.get(multi*i+shift);
        }
        step();       
        seed ^= ( seed + *reinterpret_cast<unsigned int *>(&ret) ) % INT_MAX;
        return ret;
    }	
};
#endif
