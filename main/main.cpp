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
    ColumnarCipher test;
    cout << "Decrypted" << test.decrypt("COSHSAEIADTNOXELIFWTPTTRRRAXHBMETNANSIOEFXRLESIOOPEHEGASANPTRMBODECELD") << '\n';
    
    
    return 0;
}

