#pragma once 

#include <vector>
#include <cmath>
#include <cassert>

auto concat(std::vector<double> &&x, std::vector<double> &&y){
    std::vector<double> res;
    res = x;
    res.resize(x.size() + y.size());

    for(int i=0; i<y.size();++i){
        res[x.size() + i] = y[i];
    }
    return res;
}

auto concat(std::vector<double> &x, std::vector<double> &y){
    return concat(std::move(x),std::move(y));
}

auto concat(std::vector<double> &&x, std::vector<double> &y){
       return concat(std::move(x),std::move(y));
}

auto concat(std::vector<double> &x, std::vector<double> &&y){
       return concat(std::move(x),std::move(y));
}


auto concat(std::vector<std::vector<double>> &&x, std::vector<std::vector<double>> &&y){

    assert(x.size() == y.size());
    std::vector<std::vector<double>> res;
    
    for(int i=0; i< x.size(); ++i){
        auto u = concat(x[i], y[i]);
        res.emplace_back(u);
    }

    return res;
}

auto concat(std::vector<std::vector<double>> &x, std::vector<std::vector<double>> &y){
    return concat(std::move(x),std::move(y));
}

auto concat(std::vector<std::vector<double>> &&x, std::vector<std::vector<double>> &y){
    return concat(std::move(x),std::move(y));
}

auto concat(std::vector<std::vector<double>> &x, std::vector<std::vector<double>> &&y){
    return concat(std::move(x),std::move(y));
}

template <typename T>
auto concat(std::vector<T> &&x, std::vector<T> &&y){
    assert(x.size() == y.size());

    std::vector<T> res;

    for(int i=0; i< x.size(); ++i){
        auto u = concat(x[i], y[i]);
        res.emplace_back(u);
    }
    return res;
}

template <typename T>
auto concat(std::vector<T> &x, std::vector<T> &y){
    return concat(std::move(x),std::move(y));
}

template <typename T>
auto concat(std::vector<T> &&x, std::vector<T> &y){
    return concat(std::move(x),std::move(y));
}

template <typename T>
auto concat(std::vector<T> &x, std::vector<T> &&y){
    return concat(std::move(x),std::move(y));
}