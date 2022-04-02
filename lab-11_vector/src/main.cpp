#include <iostream>

#include "tests.hpp"
#include "product.hpp"

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector_default_constructible<int>(5, 10);

    test_my_vector<product::Product>(
            product::Product("asdf", 4, 12.0),
            product::Product("qwe", -1, 7.5)
    );
    std::cout << "finished\n";

    return 0;
}
