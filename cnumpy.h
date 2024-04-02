#pragma once

#include <iostream>
#include <vector>

//TypeがTemplate型であるか
template<template <class...>class Template,class Type>
struct is_template : std::false_type
{};
template<template <class...>class Template, class... Args>
struct is_template<Template, Template<Args...>> : std::true_type
{};

template<typename T ,typename = typename std::enable_if<is_template<std::vector,std::remove_reference_t<T>>::value>>
class cnumpy{
 private:

  std::vector<T> vec;

  public:
    cnumpy(){}

    cnumpy(size_t i){
      vec.resize(i);
    }

    cnumpy(std::initializer_list<T> list){
      for(auto &a : list){
          vec.push_back(a);
      }
    }

    std::vector<T>& data(){
      return vec;

    } 

    size_t size(){
      return vec.size();
    }

    T& operator[](int i){
      return vec[i];
    }

    void print(){
      for(auto t : vec){
          std::cout << t << std::endl;


      }
    }

    template<typename U>
    void push_back(U&& a){
      vec.push_back(std::forward<U>(a));
    }

    template<typename U>
    void emplace_back(U&& a){
      vec.emplace_back(std::forward<U>(a));
    }

    auto begin() noexcept{
        return std::begin(vec);

    };    

    auto end() noexcept{
        return std::end(vec);
    };    


    decltype(auto) back() noexcept{
      return vec.back();

    }

};

#if 0
template <typename T>
class cnumpy{
  private:

  std::vector<T> vec;

  public:
    cnumpy(){}

    cnumpy(size_t i){
      vec.resize(i);
    }

    cnumpy(std::initializer_list<T> list){
      for(auto &a : list){
          vec.push_back(a);
      }
    }

    std::vector<T>& data(){
      return vec;

    } 

    size_t size(){
      return vec.size();
    }

    T& operator[](int i){
      return vec[i];
    }

    void print(){
      for(auto t : vec){
          std::cout << t << std::endl;


      }
    }

    template<typename U>
    void push_back(U&& a){
      vec.push_back(std::forward<U>(a));
    }

    template<typename U>
    void emplace_back(U&& a){
      vec.emplace_back(std::forward<U>(a));
    }

    auto begin() noexcept{
        return std::begin(vec);

    };    

    auto end() noexcept{
        return std::end(vec);
    };    


    decltype(auto) back() noexcept{
      return vec.back();

    }

};
#endif

