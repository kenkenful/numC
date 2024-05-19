#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

bool print(double t, bool end = true){
  std::cout << t << std::endl;
  return false;
}

// right value 
bool print(std::vector<double> &&t, bool end = true){
    std::cout << "[";
    for(auto &x : t){
          std::cout << x;
          if (&x != &t.back()) std::cout << " ";
    }
   
    std::cout << "]";
    if(end) std::cout << std::endl;
    return true;
}

template<typename T>
bool print(std::vector<T> &&t, bool end = true){
    std::cout << "[";
    int i=0;
    for(auto &v : t){
        i++;
        bool vec = print(std::forward<T>(v) , false);
       
        if(&v != &t.back() &&  vec != true) std::cout << std::endl;
        if(i != t.size()) std::cout <<std::endl; 

    }
    std::cout<< "]";

    if(end == true) std::cout << std::endl;
    return false;
}

// left value interface
template<typename T>
void print(std::vector<T> &t, bool end = true){ 
    print(std::move(t), end);
}















#if 0

// 単純にdoubleのときは、これが使われる。  
// right value 
void print(cnumpy<double> &&t, bool end){
    std::cout << "[";
    for(auto &x : t){
          std::cout << x;
          if (&x != &t.back()) std::cout << " ";
    }
   
    std::cout << "]";
    if(end) std::cout << std::endl;
}


// 大枠 の[  ]
template<typename T>
void print(cnumpy<T> &&t, bool end = false){
    //std::cout << "[";
    int i=0;
    for(auto &v : t){
        i++;

        // 最後のブロックに関しては改行したくない。
        if (&v != &t.back())  print(std::forward<T>(v) , false);
        else  print(std::forward<T>(v) , true);

    //    if(i == t.size()) std::cout << "]";
        std::cout << std::endl;
    }

}

// left value interface   右辺値にキャストするだけ
template<typename T>
void print(cnumpy<T> &t, bool end = false){ 
    if(getDim<std::remove_reference_t<decltype(t)>>::dim() == 1)
      print(std::move(t), true);
    else
      print(std::move(t), false);
}

#endif