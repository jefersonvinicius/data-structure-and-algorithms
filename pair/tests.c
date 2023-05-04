#include "assert.h"
#include "_utils_/data.h"
#include "./pair.h"

int main() {
    {  // create pair
        struct Pair* pair = make_pair(intp(1), intp(10));
        assert(*((int*)pair->left) == 1);
        assert(*((int*)pair->right) == 10);
    }

    return 0;
}