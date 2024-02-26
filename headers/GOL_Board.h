#ifndef GOL_BOARD_HEADER
#define GOL_BOARD_HEADER

#include <bit>
#include <iostream>

template <class TYPE, int size> class GOL_Board {
    public:
    /// @brief returns true where exactly 1 of the three inputs is true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where exactly one of the three inputs was true
    const static inline TYPE any1of3(TYPE a, TYPE b, TYPE c) {
        return a & ~b & ~c | ~a & b & ~c | ~a & ~b & c;
    }

    /// @brief returns true where exactly 2 of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where exactly two of the three inputs were true
    const static inline TYPE any2of3(TYPE a, TYPE b, TYPE c) {
        return a & b & ~c | ~a & b & c | a & ~b & c;
    }

    /// @brief returns true where none of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where none of the three inputs were true
    const static inline TYPE noneof3(TYPE a, TYPE b, TYPE c) {
        return ~a&~b&~c ;
    }

    /// @brief returns true where all three of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where all of the three inputs were true
    const static inline TYPE all3(TYPE a, TYPE b, TYPE c) {
        return a & b & c;
    }

    TYPE board[size][3];

    /// @brief Sets the GOL-Board to a predefined state
    /// @param _board a GOL-Board used to set the internal GOL-Board
    void set_board(TYPE _board[size]) {
        for (int i = 0; i<size; i++) {
            board[i][0] = _board[i];
        }
    }

    /// @brief returns the bit at position x/y as a boolean
    /// @param x x position to be returned
    /// @param y y position to be returned
    /// @param layer what layer to return: 0 (default) -> GOL Board, 1 -> LSB Board, 2 -> MSB Board
    /// @return Bit at position x/y as a boolean
    inline bool get(int x, int y, short layer = 0) {
        return (board[y%size][layer] >> (x%size)) & 1;
    }

    inline bool get(int index) {
        return get(index % size, index / size);
    }

    inline void set(int x, int y, bool value) {
        board[y%size][0] = board[y%size][0] | ((value) << (x%size));
    }

    inline void set(int index, bool value) {
        set(index % size, index / size, value);
    }

    /// @brief Upbades the LSB- and MSB-Boards based on the GOL Board, needs to be run before updating GOL-Board
    void update_msb_lsb() {
        TYPE l, r, c;
        for (int i = 0; i < size; i++) {
            l = std::rotl(board[i][0], 1), r = std::rotr(board[i][0], 1), c = board[i][0];
            board[i][1] = (c ^ l) ^ r; // LSB
            board[i][2] = (c & l) | (c & r) | (r & l);//MSB
        }
    }

    /// @brief Visualizes the GOL-Board on the console
    void visualize()  {
        std::cout << "\u250f\u2501";
        for (int i = 0; i < size; i++) { std::cout << "\u2501\u2501"; }
        std::cout << "\u2513\n";
        for (int i = 0; i < size; i++) {
            std::cout << "\u2503 ";
            for (int j = 0; j < size; j++) {
                if (get(j,i)) { std::cout << "\u25A0 "; }
                else { std::cout << "\u25A2 "; }
            }
            std::cout << "\u2503\n";
        }
        std::cout << "\u2517\u2501";
        for (int i = 0; i < size; i++) { std::cout << "\u2501\u2501"; }
        std::cout << "\u251b" << std::endl;
    }
};

#endif