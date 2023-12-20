#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
// some declarations in
// the header file.
const int BIT_SIZE = 8;
const int ASCII_BOUND = 128;
const std::vector<std::vector<double>> HAMMING_7_4 = {{1, 0, 1, 0, 1, 0, 1}, {0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 1, 1, 1, 1}};
const std::string RANDOM_KEY = "DEACB";
const int BLOCK_LENGTH = 5;
const double DEFAULT_KEY_LENGTH = (double)RANDOM_KEY.length();
const std::vector<char> ALPHABET =  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                     'U', 'V', 'W', 'X', 'Y', 'Z'};


#endif