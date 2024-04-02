#pragma once

#include <iostream>
#include <vector>
#include "meta.h"


auto slice(std::vector<std::vector<double>> &&t , char a){
    std::vector<std::vector<double>> res(t);
    return res;
}

auto slice(std::vector<std::vector<double>> &t , char a){
    return slice(std::move(t), a);
}


auto slice(std::vector<std::vector<double>> &&t, int a){
    std::vector<double> res(t[a]);
    return res;
}

auto slice(std::vector<std::vector<double>> &t, int a){
    return slice(std::move(t), a);
}

auto slice(std::vector<std::vector<double>> &&t, int a, char b){
    std::vector<double> res(t[a]);
    return res;
}

auto slice(std::vector<std::vector<double>> &t, int a, char b){
    return slice(std::move(t), a, b);
}

auto slice(std::vector<std::vector<double>> &&t, char a, int b){
    std::vector<double> res(t.size());
    for(int i=0; i < t.size(); ++i){
        res[i] = t[i][b];
    }
    return res;
}

auto slice(std::vector<std::vector<double>> &t, char a, int b){   
    return slice(std::move(t), a, b);
}

auto slice(std::vector<std::vector<double>> &&t, int a, int b){
    double res = t[a][b];
    return res;
}


auto slice(std::vector<std::vector<double>> &t, int a, int b){
    double res = t[a][b];
    return res;
}


auto slice(std::vector<std::vector<double>> &&t, char a, char b){
     std::vector<std::vector<double>> res(t);
    return res;
}

auto slice(std::vector<std::vector<double>> &t, char a, char b){
    std::vector<std::vector<double>> res(t);
    return res;
}



// 3次元以上
template<typename T>
auto slice(std::vector<std::vector<T>> &&t){
    std::vector<std::vector<T>> res(t);
    return res;
}

template<typename T>
auto slice(std::vector<std::vector<T>> &t){
    slice(std::move(t));
}


template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &&t, int a){
    std::vector<T> res(t[a]);
    return res;
}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &t, int a){
    std::vector<T> res(t[a]);
    return res;
}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &&t, char a){
    std::vector<std::vector<T>> res(t);
    return res;
}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &t, char a){
    std::vector<std::vector<T>> res(t);
    return res;
}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &&t, int a, Tail&&... tail){
    return slice(std::move(t[a]), std::forward<Tail>(tail)...);

}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &t, int a, Tail&&... tail){
    return slice(std::move(t[a]), std::forward<Tail>(tail)...);
}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &&t, char a, Tail&&... tail){
    //std::cout << "q" << std::endl;
    typename vector<GetCharNum<sizeof...(tail), Tail...>::value() + 1>::type res(t.size());

   // std::cout << GetCharNum<sizeof...(tail), Tail...>::value() << std::endl;

    for(int i=0; i < t.size(); ++i){
            res[i] = slice(std::move(t[i]), std::forward<Tail>(tail)...);
    }
    
    return res;

}

template<typename T , typename ...Tail>
auto slice(std::vector<std::vector<T>> &t, char a, Tail&&... tail){
    
    return slice(std::move(t), a, std::forward<Tail>(tail)...);

}