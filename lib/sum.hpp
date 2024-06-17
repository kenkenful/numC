#pragma once


#include <vector>
#include "add.hpp"


auto sum(std::vector<double> &&a){
    int res = 0;
    for(auto p : a){
        res += p;
    }
    return res;
}

auto sum(std::vector<double> &a){
  
    return sum(std::move(a));
}


auto sum(std::vector<std::vector<double>> &&a){
    int res = 0;
    for(auto &p : a)
        for(auto q : p)
            res += q;
    return res;
}

auto sum(std::vector<std::vector<double>> &a){
    return sum(std::move(a));
}


auto sum(std::vector<std::vector<double>> &&a, int axis){
    
    std::vector<double> res;

    if(axis == 0){
        for(int i= 0; i < a[0].size(); ++i){
            int temp = 0;
            for(int j = 0; j< a.size(); ++j){
                temp += a[j][i];
            }
            res.emplace_back(temp);
        }
    }else if(axis == 1){
        for(auto &p : a){
            int temp = 0;
            for(auto q : p){
                temp += q;
            }
            res.emplace_back(temp);
        }
    }
    return res;
}

auto sum(std::vector<std::vector<double>> &a, int axis){
    
    return sum(std::move(a), axis);
    
}


template <typename T>
auto sum(std::vector<T> &&a){
    int res = 0;

    for(auto &i : a){
        res = sum(std::move(i));
    }

    return res;
}

template <typename T>
auto sum(std::vector<T> &a){

    return sum(std::move(a));
}


template <typename T>
auto sum(std::vector<T> &&a, int axis){
    T res;

    if(axis != 0){
        for(auto &i : a){
           res.emplace_back(sum(std::move(i), axis-1));
        }

    }else{
        res = a[0];
        for(int i=1; i<a.size(); ++i){
            res = res + a[i];
        }
    }

    return res;
}

template <typename T>
auto sum(std::vector<T> &a, int axis){
    return sum(std::move(a), axis);
}