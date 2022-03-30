#include <iostream>

#include "my_vector.hpp"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price);

private:
    char *name_;
    int quantity_;
    double price_;
};

}  // namespace product

void test_specification() {
    static_assert(std::is_copy_constructible<containers::my_vector<int>>::value);
    static_assert(std::is_destructible<containers::my_vector<int>>::value);
    static_assert(std::is_copy_constructible<containers::my_vector<product::Product>>::value);
    static_assert(std::is_destructible<containers::my_vector<product::Product>>::value);
    static_assert(!std::is_default_constructible<product::Product>::value);
}


int main() {

    test_specification();




//	containers::my_vector<int> v;
//	v.push_back(2);
//	const int n{3};
//	v.push_back(n);
//	std::cout << v << std::endl;

    //test_my_vector<int>(5, 10);
    //test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
