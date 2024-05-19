#pragma once 

#include <iostream>
#include <vector>


auto swap(std::vector<std::vector<double>> &&t){
    std::vector<std::vector<double>> res(t[0].size(), std::vector<double>(t.size()));

    for(int i=0; i< t[0].size();++i){
        for(int j=0; j< t.size(); ++j){
            res[i][j] = t[j][i];
        }
    }

    return res;

}


auto swap(std::vector<std::vector<double>> &&t, int cnt){
    std::vector<std::vector<double>> res(t[0].size(), std::vector<double>(t.size()));

    for(int i=0; i< t[0].size();++i){
        for(int j=0; j< t.size(); ++j){
            res[i][j] = t[j][i];
        }
    }

    return res;

}


template <typename T>
auto swap(std::vector<std::vector<T>> &&t){
    std::vector<std::vector<T>> temp(t[0].size(), std::vector<T>(t.size()));

    for(int i=0; i< t[0].size();++i){
        for(int j=0; j< t.size(); ++j){
            temp[i][j] = t[j][i];
        }
    }

    std::vector<std::vector<T>> res(temp.size());

    for(int i=0; i<temp.size(); ++i){
        res[i] = swap(std::move(temp[i]));

    }

    return res;

}

template <typename T>
auto swap(std::vector<std::vector<T>> &&t, int cnt){
    std::vector<std::vector<T>> temp(t[0].size(), std::vector<T>(t.size()));

    for(int i=0; i< t[0].size();++i){
        for(int j=0; j< t.size(); ++j){
            temp[i][j] = t[j][i];
        }
    }

    if(--cnt == 0) return temp;

    std::vector<std::vector<T>> res(temp.size());

    for(int i=0; i<temp.size(); ++i){
        res[i] = swap(std::move(temp[i]), cnt);

    }

    return res;

}

template <typename U>
auto T(std::vector<std::vector<U>> &&t){

    std::vector<std::vector<U>> res;
    std::vector<std::vector<U>> u = t;
    
    for(int i = getDim<std::remove_reference_t<U>>::dim() + 1; i>0 ; --i){
      //std::cout << i << std::endl; 
     res = swap(std::move(u),i);
      u = res;  
     //print(u);
      //std::cout << "--------------" <<std::endl;

    }
    return res;

}
template <typename U>
auto T(std::vector<std::vector<U>> &t){

    return T(std::move(t));

}