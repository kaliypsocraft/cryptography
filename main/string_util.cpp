#include <iostream>
#include <algorithm>
#include "constants.h"
#include "string_util.h"

using std::cout, std::cin, std::find;
// Custom comparison function based on a specific ordering
bool customOrder(char a, char b) {
    // Define your custom ordering logic here
    std::string ordering = RANDOM_KEY;
    
    auto findOrder = [ordering](char c) {
        auto it = std::find(std::begin(ordering), std::end(ordering), c);
        return it != std::end(ordering) ? it - std::begin(ordering) : ordering.size();
    };

    return findOrder(a) < findOrder(b);
}

/// @brief Adds spaces to a desired key length. Utilised for enciphering plain text into a readable format.
/// @param s 
/// @return 
std::string formatMessage(std::string s) {
    while (s.length() % DEFAULT_KEY_LENGTH != 0) {
        s += ' ';
    }
    return s;
}

