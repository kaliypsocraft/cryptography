#include <iostream>
#include "cryptography.h"
#include <gmp.h>
#include "constants.h"
#include <gmpxx.h>
#include <vector>
#include <string>
#include <math.h>
#include "sort.h"
#include <random>
#include <bitset>
#include <math.h>
#include <iomanip>
#include "matrices.h"
#include "string_util.h"

using std::vector, std::cout, std::cin, std::find;

int main() {

    QuickSort<char> testing;
    vector<char> test1 = {'D', 'G', 'A', 'L'};
    cout << "Unsorted" << '\n';
    for (const auto& elem : test1) {
        cout << elem << " ";
    }
    cout << '\n';
    testing.sort(test1, 0, test1.size() - 1);
    cout << "Sorted" << '\n';
    for (const auto& elem : test1) {
        cout << elem << " ";
    }
    cout << '\n';
   
    
    
    return 0;
}

