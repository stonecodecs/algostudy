#include "select.h"

int main(int argc, char** argv) {
    while(true) {
        int nth_smallest{};
        std::cin >> nth_smallest;
        std::vector<int> t{5,2,1,9,8,3,7,11,15,6};
        int value = rselect(t, nth_smallest); // t passed by value
        std::cout << "\nvalue: " << value << '\n';
    }

    return 0;
}