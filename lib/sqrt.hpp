#pragma once 

#include <vector>
#include <cmath>

auto sqrt(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = sqrt(x[i]);
    }   


    return res;
}

template <typename T>
auto sqrt(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = sqrt(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template <typename T>
auto sqrt(std::vector<T>& x){

    return sqrt(std::move(x));
}
