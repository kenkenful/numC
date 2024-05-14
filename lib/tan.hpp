#pragma once 

#include <vector>
#include <cmath>

auto tan(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = tan(x[i]);
    }   


    return res;
}

template <typename T>
auto tan(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = tan(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template <typename T>
auto tan(std::vector<T>& x){

    return tan(std::move(x));
}
