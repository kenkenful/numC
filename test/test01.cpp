
#include "../lib/numc.hpp"


int main(){
    std::vector<double> a = {1,2,3,4,5};
    std::vector<decltype(a)> b = {a,a,a,a,a};
    std::vector<decltype(b)> c = {b,b,b,b};

    std::cout << "1 dim" << std::endl;
    print(a);

    std::cout << "2 dim" << std::endl;
    print(b);

    std::cout << "3 dim" << std::endl;
    print(c);



}