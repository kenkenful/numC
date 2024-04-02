#pragma once 

#include <cmath>
#include "cnumpy.h"


auto sin(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = sin(x[i]);
    }   


    return res;
}

template <typename T>
auto sin(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = sin(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値インターフェース
template <typename T>
auto sin(std::vector<T>& x){
    return sin(std::move(x));
}


