#pragma once

#include <cmath>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"
#include "exp.h"
#include "log.h"
#include "cos.h"
#include "sin.h"


template<typename T>
auto tanh(double x){

    return  (exp(x) - exp(-1 * x)) / (exp(x) + exp(-1 * x));
}

template<typename T>
auto tanh(std::vector<T>&& x){

    return  (exp(x) - exp(-1 * x)) / (exp(x) + exp(-1 * x));
}

// 左辺値のインターフェース
template<typename T>
auto tanh(std::vector<T>& x){
    return  tanh(std::move(x));
}


template<typename T>
auto sigmoid(double x){
  
    return 1.0/(1.0 + exp(-1 * x));

}

template<typename T>
auto sigmoid(std::vector<T>&& x){
  
    return 1.0/(1.0 + exp(-1 * x));

}

// 左辺値のインターフェース
template<typename T>
auto sigmoid(std::vector<T>& x){
  
    return sigmoid(std::move(x));
}





auto dot(std::vector<double>&& x, std::vector<double> &&y){
    int res;
    for(int i = 0; i < x.size(); ++i){
        res += x[i] * y[i];
    }
    return res;
}

#if 0
auto dot(std::vector<double>& x, std::vector<double> &&y){
    return dot(std::move(x), std::forward<std::vector<double>>(y));
}

auto dot(std::vector<double>&& x, std::vector<double> &y){
    return dot(std::forward<std::vector<double>>(x), std::move(y));
}

auto dot(std::vector<double>& x, std::vector<double> &y){
    return dot(std::move(x), std::move(y));
}

#endif


auto dot(std::vector<std::vector<double>>&& x, std::vector<std::vector<double>> &&y){
    
    std::vector<std::vector<double>> res(x.size(), std::vector<double>(y[0].size()));

    for(int i = 0; i < x.size(); ++i){
        for(int j = 0; j < y[0].size(); ++j){
            for(int k = 0; k < y.size(); ++k){
                res[i][j] += x[i][k] * y[k][j];
            }
        }
    }

    return res;

}

template <typename T>
auto dot(std::vector<T>&& x, std::vector<T> &&y){

    std::vector<T> res; 

    for(int i=0; i<x.size(); ++i){
        res.emplace_back(dot(std::forward<T>(x[i]), std::forward<T>(y[i])));
    }

    return res;

}

template <typename T>
auto dot(std::vector<T>& x, std::vector<T> &y){
    return dot(std::forward<std::vector<T>>(x), std::forward<std::vector<T>>(y));
}

template <typename T>
auto dot(std::vector<T>& x, std::vector<T> &&y){
    return dot(std::move(x), std::forward<std::vector<T>>(y));
}

template <typename T>
auto dot(std::vector<T>&& x, std::vector<T> &y){
    return dot(std::forward<std::vector<T>>(x), std::move(y));
}

#if 1


template<typename T>
auto exp(cnumpy<T>&& x){

    cnumpy<T> res(x.size());

    for(int i=0; i<x.size(); ++i){
      res[i] = exp(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template<typename T>
auto exp(cnumpy<T>& x){

    return exp(std::move(x));
}



template<typename T>
auto tanh(cnumpy<T>&& x){

    return  (exp(x) - exp(-1 * x)) / (exp(x) + exp(-1 * x));
}

// 左辺値のインターフェース
template<typename T>
auto tanh(cnumpy<T>& x){
    return  tanh(std::move(x));
}




template<typename T>
auto sigmoid(cnumpy<T>&& x){
  
    return 1.0/(1.0 + exp(-1 * x));

}

// 左辺値のインターフェース
template<typename T>
auto sigmoid(cnumpy<T>& x){
  
    return sigmoid(std::move(x));
}


template<typename T>
auto log(cnumpy<T>&& x){

    cnumpy<T> res(x.size());

    for(int i=0; i<x.size(); ++i){
      res[i] = log(std::forward<T>(x[i]));
    }

    return res;
}

// 左辺値のインターフェース
template<typename T>
auto log(cnumpy<T>& x){

    return log(std::move(x));
}



template<typename T>
auto cos(cnumpy<T>&& x){

    cnumpy<T> res(x.size());

    for(int i=0; i<x.size(); ++i){
      res[i] = cos(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template<typename T>
auto cos(cnumpy<T>& x){

    return cos(std::move(x));
}


template<typename T>
auto sin(cnumpy<T>&& x){

    cnumpy<T> res(x.size());

    for(int i=0; i<x.size(); ++i){
      res[i] = sin(std::forward<T>(x[i]));
    }


    return res;
}

// 左辺値のインターフェース
template<typename T>
auto sin(cnumpy<T>& x){

    return sin(std::move(x));
}

template <typename T>
auto dot(cnumpy<T> &&x, cnumpy<T> &&y){

    cnumpy<T> res ;

    for(int i=0; i<x.size(); ++i){
        res.emplace_back(dot(std::forward<T>(x[0]), std::forward<T>(y[0])));
    }
    return res;
}

template <typename T >
auto dot(cnumpy<T>& x, cnumpy<T> &&y){

    return dot(std::move(x), std::forward<cnumpy<T>>(y));

}

template <typename T>
auto dot(cnumpy<T>&& x, cnumpy<T> &y){

    return dot(std::forward<cnumpy<T>>(x) , std::move(y));

}

template <typename T >
auto dot(cnumpy<T>& x, cnumpy<T> &y){

    return dot(std::move(x) , std::move(y));

}
#endif