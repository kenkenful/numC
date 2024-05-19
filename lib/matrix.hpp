#pragma once 

#include <vector>
#include <cmath>

auto zeros(int a){
    std::vector<double> res(a);

    return res;
}

auto zeros(int a, int b){
    std::vector<std::vector<double>> res(a, std::vector<double>(b));

    return res;
}


template <class... Tail>
auto zeros(int a, Tail&&... tail){
    std::vector<decltype(zeros(std::forward<Tail>(tail)...))> res;
    for(int i=0; i<a ;++i){
        res.emplace_back(zeros(std::forward<Tail>(tail)...));
    }
    return res;
}

auto zeros_like(std::vector<double> &w){
    std::vector<double> res(w.size());
    return res;
}

auto zeros_like(std::vector<std::vector<double>> &w){
    std::vector<std::vector<double>> res(w.size(), std::vector<double>(w[0].size()));

    return res;

}

template<typename T>
auto zeros_like(std::vector<T> &w) {
    std::remove_reference_t<decltype(w)> res;

    for(int i=0; i< w.size(); ++i){
        res.emplace_back(zeros_like(w[i]));
    }

    return res;
}

auto ones(int a){
    std::vector<double> res(a);
    for(int i=0; i<a ;++i){
        res[i] = 1.0;
    }
    return res;
}

auto ones(int a, int b){
    std::vector<std::vector<double>> res(a, std::vector<double>(b));
    for(int i=0; i<a ;++i){
        for(int j=0;j<b;++j){
            res[i][j] = 1.0;
        }
    }
    return res;
}

template <class... Tail>
auto ones(int a, Tail&&... tail){
    std::vector<decltype(ones(std::forward<Tail>(tail)...))> res;
    for(int i=0; i<a ;++i){
        res.emplace_back(ones(std::forward<Tail>(tail)...));
    }
    return res;
}

auto ones_like(std::vector<double> &w){
    std::vector<double> res(w.size());
    for(int i=0; i<w.size(); ++i)
        res[i] = 1.0;
    return res;
}

auto ones_like(std::vector<std::vector<double>> &w){
    std::vector<std::vector<double>> res(w.size(), std::vector<double>(w[0].size()));
    for(int i=0; i<w.size(); ++i)
        for(int j=0; j<w.size(); ++j)
        res[i][j] = 1.0;
    return res;
}

template<typename T>
auto ones_like(std::vector<T> &w) {
    std::remove_reference_t<decltype(w)> res;

    for(int i=0; i< w.size(); ++i){
        res.emplace_back(ones_like(w[i]));
    }

    return res;
}

