#include "../headers/GOL_Hash.h"

GOL_Hash::GOL_Hash(std::string _path) : gol_board(SIZE_X,SIZE_Y,0), salt(SIZE_X,SIZE_Y), input_stream(_path), path(_path), hashed(false), salted(false) {
    
}

void GOL_Hash::hashing() {
    hashed = true;
    BitBoard data(SIZE_X,SIZE_Y);
    auto fileSize = std::filesystem::file_size(path);
    std::vector<char> buffer(HASH_SIZE);
    std::cout << "Starting to GOL-HASH a file of size " << fileSize << " bytes..." << std::endl;
    while (!input_stream.eof()) {
        input_stream.read(buffer.data(), buffer.size());
        data.set(boost::dynamic_bitset<unsigned char>(buffer.begin(), buffer.end()));
        gol_board.apply_xormap(data);
        gol_board.steps(BLOCK_STEPS);
    }
    if (salted) {gol_board.apply_xormap(salt);}
    gol_board.steps(SALT_STEPS);
}

BitBoard GOL_Hash::get_Hash() {
    if (hashed) {return gol_board.get_board();}
    hashing();
    return gol_board.get_board();
}

std::string GOL_Hash::get_Str_Hash() {
    if (!hashed) {hashing();}
    std::string buffer;
    boost::to_string(gol_board.get_board().get(), buffer);
    std::stringstream reader(buffer);
    std::stringstream result;

    while (reader)
    {
        std::bitset<64> digit;
        reader >> digit;
        result << std::hex << digit.to_ulong();
    }

    return result.str();
}
