
#include "../lib/numc.hpp"


int main(){
    std::vector<double> a = {1,2,3,4,5};              // (1,5) matrix
    std::vector<decltype(a)> b = {a,a,a,a,a};         // (5,5) matrix
    std::vector<decltype(b)> c = {b,b,b,b};           // (5,5,4) matrix   

    std::vector<decltype(a)> e = {a,a,a,a} ;           // (5,4) matrix

    std::cout << "-------calc 1-------" << std::endl;

    print(a + 4 - a + 1.3 * b + c + 7);

    std::cout << "-------calc 2-------" << std::endl;
    print(c- a + 4 - a + 1.3 * b + c * 100 + 7);

    std::cout << "-------calc 3-------" << std::endl;
    print(c- a + 4 - a + b * (1.3 * b + c * 100) + 7);

    std::cout << "-------calc 4-------" << std::endl;
    print(c- a + 4 - a + b * (1.3 * b + c * 100)/b + 7);


}