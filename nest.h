#pragma once

#include <iostream>
#include <vector>


// std::vectorをネスト型を返すメタ関数
template <size_t N>
struct vector
{
public:
  using type = std::vector<typename vector<(N - 1)>::type>;
};

template <>
struct vector<0>
{
public:
    using type = double;
};

// std::vectorのネスト数を返すメタ関数
template <typename T>
struct getDim {
  static constexpr int dim() {
    return 0;
  }
};

template <typename T>
struct getDim<std::vector<T>> {

  static constexpr int dim() {
    return 1 + getDim<T>::dim();
  }
};



