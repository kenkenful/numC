#include <iostream>
#include <vector>
#include "calc.h"
#include "print.h"

int main(){
    std::vector<std::vector<double>> a = {{1,2,3}, {1,2,3}};
    std::vector<std::vector<double>> b = {{3,3,3}, {2,2,7},{4,5,6} };
    std::vector<std::vector<double>> c = {{2,2,7},{4,5,6}};


    auto ans = c- a * (dot(a,b)  + a);


    print(ans);





}