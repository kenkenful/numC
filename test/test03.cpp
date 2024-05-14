
#include "../lib/numc.hpp"


int main(){
    std::vector<double> a = {1.6,2.3,3.4,4.9,5.0};              // (1,5) matrix
    std::vector<decltype(a)> b = {a,a,a,a,a};         // (5,5) matrix
    std::vector<decltype(b)> c = {b,b,b,b};           // (5,5,4) matrix   

    std::vector<decltype(a)> e = {a,a,a,a} ;           // (5,4) matrix

    std::cout << "-------calc 1-------" << std::endl;

    print(10.4 * sin(a + 4) - cos(a) / 2.0);

    std::cout << "-------calc 2-------" << std::endl;
    print(tan(c- a)*15.9 * c -c);



}