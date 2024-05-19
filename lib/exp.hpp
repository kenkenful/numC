#pragma once
#include <cmath>
#include <vector>

auto exp(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0;i< x.size();++i){
            res[i] = exp(x[i]);
    }   


    return res;
}

template <typename T>
auto exp(std::vector<T>&& x){

    std::vector<T> res(x.size());

    for(int i=0;i< x.size();++i){
      res[i] = exp(std::forward<T>(x[i]));
    }


    return res;
}


template <typename T>
auto exp(std::vector<T>& x){

    return exp(std::move(x));
}
