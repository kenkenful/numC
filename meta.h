#pragma once

#include <iostream>
#include <vector>


// return number of nested num of std::vector
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

// return nested std::vector<>
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


#if 0
 int numOfChar() {
  return 0;
}  

template<typename Head, typename ...Tail>
 int numOfChar(Head&& head, Tail&& ...tail){
  
  if(std::is_same<std::remove_reference_t<Head>, char>::value) {
    
    return 1 + numOfChar(std::forward<Tail>(tail)...);

  }

  return  numOfChar(std::forward<Tail>(tail)...);

}


template < class ...TypeBody>
struct ch;

template <class TypeHead, class ...TypeBody>
struct ch<TypeHead, TypeBody...>  : public ch<TypeBody...>
{
  static constexpr int num() {
    return ch<TypeHead>::num;
  }
};

template <>
struct ch<char> {

  static constexpr int num() {
    return 1;
  }
};

#endif



template <int N, class ...Types>
class GetCharNum;

template <int N, class TypeHead, class ...TypeBody>
class GetCharNum<N, TypeHead, TypeBody...> 
{
  public:
    static constexpr int value() {

      if(std::is_same<std::remove_reference_t<TypeHead>, char>::value) {
        return 1 + GetCharNum<N-1, TypeBody...>::value();  
      }

      return  GetCharNum<N-1, TypeBody...>::value();  

    }
};

template <class TypeHead, class ...TypeBody>
class GetCharNum<0, TypeHead, TypeBody...>{
    public:
    static constexpr int value() {

      return 0;  
    }

};

template <class ...TypeBody>
class GetCharNum<0, TypeBody...>{
    public:
    static constexpr int value() {

       return 0;  
    }

};