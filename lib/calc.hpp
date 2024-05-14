#pragma once

#include "add.hpp"
#include "sub.hpp"
#include "mul.hpp"
#include "div.hpp"
#include "exp.hpp"
#include "log.hpp"
#include "cos.hpp"
#include "sin.hpp"
#include "tan.hpp"



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


