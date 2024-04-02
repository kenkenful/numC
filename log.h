#pragma once 

#include <cmath>
#include "cnumpy.h"


auto log(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = log(x[i]);
    }   

    return res;
}

template <typename T>
auto log(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = log(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template<typename T>
auto log(std::vector<T>& x){

    return log(std::move(x));
}
