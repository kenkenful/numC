#pragma once 

#include <vector>
#include <random>
#include <algorithm>


auto random_rand(int a){
    std::vector<double> res(a);
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // 離散一様分布 U(0, 1)
    // テンプレートパラメータを double にしているため, 生成される乱数は double 型整数
    std::uniform_real_distribution<double> dist(0, 1);

    for(int i=0; i<a ;++i){
        res[i] = dist(engine);
    }

    return res;
}

auto random_rand(int a, int b){
    std::vector<std::vector<double>> res(a, std::vector<double>(b));
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // 離散一様分布 U(0, 1)
    // テンプレートパラメータを double にしているため, 生成される乱数は double 型整数
    std::uniform_real_distribution<double> dist(0, 1);

    for(int i=0; i<a ;++i){
        for(int j=0;j<b;++j){
            res[i][j] = dist(engine);
        }
    }

    return res;
}


template <class... Tail>
auto random_rand(int a, Tail&&... tail){
    std::vector<decltype(random_rand(std::forward<Tail>(tail)...))> res;
    
    for(int i=0; i<a ;++i){
        res.emplace_back(random_rand(std::forward<Tail>(tail)...));
    }

    return res;
}

auto random_randn(int a){
    std::vector<double> res(a);

    double sigma = 1.00;
    std::random_device seed;
    std::mt19937 engine(seed());
    std::normal_distribution<double> dist(0.0, sigma);

    for(int i=0; i<a ;++i){
        res[i] = dist(engine);
        
    }

    return res;
}

auto random_randn(int a, int b){
    std::vector<std::vector<double>> res(a, std::vector<double>(b));

    double sigma = 1.00;
    std::random_device seed;
    std::mt19937 engine(seed());
    std::normal_distribution<double> dist(0.0, sigma);

    for(int i=0; i<a ;++i){
        for(int j=0;j<b;++j){
            res[i][j] = dist(engine);
        }
    }

    return res;
}

template <class... Tail>
auto random_randn(int a, Tail&&... tail){
    std::vector<decltype(random_randn(std::forward<Tail>(tail)...))> res;
    
    for(int i=0; i<a ;++i){
        res.emplace_back(random_randn(std::forward<Tail>(tail)...));
    }

    return res;
}