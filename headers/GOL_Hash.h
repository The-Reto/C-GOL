#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "C_GOL.h"
#include "BitBoard.h"
#include <fstream>
#include <filesystem>
#include <boost/algorithm/hex.hpp>

class GOL_Hash {
    
    C_GOL gol_board;
    BitBoard salt;
    std::basic_ifstream<char> input_stream;
    unsigned long input_size;
    bool hashed, salted;
    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1, SALT_STEPS = 64;
    
    void hashing();
    
    public:
    GOL_Hash(std::string _path);
    
    auto get_input_stream();
    
    void set_salt();
    BitBoard get_salt();
    
    boost::dynamic_bitset<unsigned char> get_Hash();
    BitBoard get_graph_Hash();
    std::string get_Str_Hash();
    
};
#endif
