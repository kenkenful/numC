#pragma once 

#include <vector>
#include <cassert>

auto reshape(std::vector<double> &x, int a){
    assert(a == x.size());
    std::vector<double> res(a);
    res = x;

    return res;
}

auto reshape(std::vector<double> &x, int a, int b){
    //assert(a * b == x.size());
    std::vector<std::vector<double>> res(a, std::vector<double>(b));
    
    for(int i=0;i<a;++i){
        for(int j=0;j<b;++j){
            res[i][j] = x[j + i*b];
        }
    }
    return res;
}

template <class... Tail>
auto reshape(std::vector<double> &x, int a, Tail&&... tail){
    std::vector<decltype(reshape(x, std::forward<Tail>(tail)...))> res;
    
    assert(x.size()%a == 0);
    int n = x.size() / a;

    for(int i=0; i<a; ++i){
        std::vector<double> temp;
        for(int j=0; j<n; ++j){
            temp.emplace_back(x[j + i*n]);
        }
        res.emplace_back(reshape(temp, std::forward<Tail>(tail)...));
    }

    return res;
}

