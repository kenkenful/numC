#pragma once 

#include <vector>
#include <cmath>

auto cos(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = cos(x[i]);
    }   


    return res;
}

template <typename T>
auto cos(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = cos(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template <typename T>
auto cos(std::vector<T>& x){

    return cos(std::move(x));
}
