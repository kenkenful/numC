
#include <vector>
#include <iostream>
#include <cmath>
#include <type_traits>

#include <iterator>


#if 1


#endif


#if 1


//  add
auto operator+(std::vector<double>&& x, double y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i]+y;
    }

    return res;
}

template<typename T>
auto operator+(std::vector<T>&& x, double y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) + y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator+(std::vector<T>& x, double y){ 
    return std::move(x) + y;

}

////////////////////////////////

auto operator+(double x, std::vector<double>&& y){ 
    std::vector<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x + y[i];
    }

    return res;
}

template<typename T>
auto operator+(double x, std::vector<T>&& y){ 
    std::vector<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x + std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator+(double x, std::vector<T>& y){ 
    return x + std::move(y);

}

////////////////////////////////

auto operator+(std::vector<double>&& x, std::vector<double>&& y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i]+y[i];
    }

    return res;
}

template<typename T>
auto operator+(std::vector<T>&& x, std::vector<T>&& y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) + std::forward<T>(y[i]);
    }

    return res;
}

// left left interface
template<typename T>
auto operator+(std::vector<T>& x, std::vector<T>& y){ 
    return std::move(x) + std::move(y);

}

// right left interface
template<typename T>
auto operator+(std::vector<T>&& x, std::vector<T>& y){ 
    return std::forward<std::vector<T>>(x) + std::move(y);

}

// left right interface
template<typename T>
auto operator+(std::vector<T>& x, std::vector<T>&& y){ 
    return std::move(x) + std::forward<std::vector<T>>(y);

}


//  multi

auto operator*(std::vector<double>&& x, double y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i]*y;
    }

    return res;
}

template<typename T>
auto operator*(std::vector<T>&& x, double y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) * y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(std::vector<T>& x, double y){ 
    return std::move(x) * y;

}


////////////////////////////////

auto operator*(double x, std::vector<double>&& y){ 
    std::vector<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x * y[i];
    }

    return res;
}

template<typename T>
auto operator*(double x, std::vector<T>&& y){ 
    std::vector<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x * std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(double x, std::vector<T>& y){ 
    return x * std::move(y);

}

////////////////////////////////

auto operator*(std::vector<double>&& x, std::vector<double>&& y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i]*y[i];
    }

    return res;
}

template<typename T>
auto operator*(std::vector<T>&& x, std::vector<T>&& y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i])*std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(std::vector<T>& x, std::vector<T>& y){ 
    return std::move(x) * std::move(y);

}

// right left interface
template<typename T>
auto operator*(std::vector<T>&& x, std::vector<T>& y){ 
    return std::forward<std::vector<T>>(x) * std::move(y);

}

// left right interface
template<typename T>
auto operator*(std::vector<T>& x, std::vector<T>&& y){ 
    return std::move(x) * std::forward<std::vector<T>>(y);

}

////////////////////////////////


auto exp(std::vector<double>&& x){

    std::vector<double> res(x.size());

    for(int i=0; i< x.size();++i){
            res[i] = exp(x[i]);
    }

    return res;
}

template<typename T>
auto exp(std::vector<T>&& x){

    std::vector<T> res;

    for(auto &v : x){
      res.push_back(exp(std::move(v)));
    }

    return res;
}

template<typename T>
auto tanh(std::vector<T>&& x){
    //return  (exp(x) - exp(-1 * x)) / (exp(x) + exp(-1 * x));

    return  exp(std::forward<std::vector<T>>(x));
}


#endif



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


    T& back() noexcept{
      return vec.back();

    }

};

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

template <typename T>
struct getDim<cnumpy<T>> {

  static constexpr int dim() {
    return 1 + getDim<T>::dim();
  }

};


#if 1

// right value 
void print(std::vector<double> &&t, bool end){
    std::cout << "[";
    for(auto &x : t){
          std::cout << x;
          if (&x != &t.back()) std::cout << " ";
    }
   
    std::cout << "]";
    //if(end) std::cout << "i";
    //else std::cout << "f";
}


template<typename T>
void print(std::vector<T> &&t, bool end){
    std::cout << "[";
    int i=0;
    for(auto &v : t){
        i++;
        
        // 最後のブロックに関しては改行したくない。
        if (&v != &t.back())  print(std::forward<T>(v) , false);
        else  print(std::forward<T>(v) , true);
        
        if(i == t.size()) std::cout << "]";

        //最後のブロックであって、さらにブロックの最後の行なら改行しない。
        if(end != true || i != t.size()) std::cout << std::endl;
    }
    
}

// left value interface
template<typename T>
void print(std::vector<T> &t, bool end = false){ 
    print(std::move(t), false);
}


#if 1     // 単純にdoubleのときは、これが使われる。  
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
#endif


// 大枠 の[  ]
template<typename T>
void print(cnumpy<T> &&t, bool end = false){
    std::cout << "[";
    int i=0;
    for(auto &v : t){
        i++;

        // 最後のブロックに関しては改行したくない。
        if (&v != &t.back())  print(std::forward<T>(v) , false);
        else  print(std::forward<T>(v) , true);

        if(i == t.size()) std::cout << "]";
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



//  add
auto operator+(cnumpy<double>&& x, double y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i]+y;
    }

    return res;
}

template<typename T>
auto operator+(cnumpy<T>&& x, double y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) + y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator+(cnumpy<T>& x, double y){ 
    return std::move(x) + y;

}

////////////////////////////////

auto operator+(double x, cnumpy<double>&& y){ 
    cnumpy<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x + y[i];
    }

    return res;
}

template<typename T>
auto operator+(double x, cnumpy<T>&& y){ 
    cnumpy<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x + std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator+(double x, cnumpy<T>& y){ 
    return x + std::move(y);

}

////////////////////////////////

auto operator+(cnumpy<double>&& x, cnumpy<double>&& y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i]+y[i];
    }

    return res;
}

template<typename T>
auto operator+(cnumpy<T>&& x, cnumpy<T>&& y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) + std::forward<T>(y[i]);
    }

    return res;
}

// left left interface
template<typename T>
auto operator+(cnumpy<T>& x, cnumpy<T>& y){ 
    return std::move(x) + std::move(y);

}

// right left interface
template<typename T>
auto operator+(cnumpy<T>&& x, cnumpy<T>& y){ 
    return std::forward<cnumpy<T>>(x) + std::move(y);

}

// left right interface
template<typename T>
auto operator+(cnumpy<T>& x, cnumpy<T>&& y){ 
    return std::move(x) + std::forward<cnumpy<T>>(y);

}

#endif



auto operator*(cnumpy<double>&& x, double y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i]*y;
    }

    return res;
}

template<typename T>
auto operator*(cnumpy<T>&& x, double y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) * y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(cnumpy<T>& x, double y){ 
    return std::move(x) * y;

}


///// val  * vector /////////

auto operator*(double x, cnumpy<double>&& y){ 
    cnumpy<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x * y[i];
    }

    return res;
}

template<typename T>
auto operator*(double x, cnumpy<T>&& y){ 
    cnumpy<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x * std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(double x, cnumpy<T>& y){ 
    return x * std::move(y);

}

////////////////////////////////

auto operator*(cnumpy<double>&& x, cnumpy<double>&& y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i]*y[i];
    }

    return res;
}

template<typename T>
auto operator*(cnumpy<T>&& x, cnumpy<T>&& y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i])*std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator*(cnumpy<T>& x, cnumpy<T>& y){ 
    return std::move(x) * std::move(y);

}

// right left interface
template<typename T>
auto operator*(cnumpy<T>&& x, cnumpy<T>& y){ 
    return std::forward<cnumpy<T>>(x) * std::move(y);

}

// left right interface
template<typename T>
auto operator*(cnumpy<T>& x, cnumpy<T>&& y){ 
    return std::move(x) * std::forward<cnumpy<T>>(y);

}









int main(){

  using type0 = double;
  using type1 = std::vector<double>;
  using type2 = std::vector<std::vector<double>>;
  using type3 =  std::vector<std::vector<std::vector<double>>>;
  using type4 =  std::vector<std::vector<std::vector<std::vector<double>>>>;

    type1 a = {1,2,3};

    type2 v = {{1,1,1},{2,2,2},{3,3,3}};
    type3 r = {v,v,v} ;
   
    
    type3 p = {v,v,v} ;
    
    type4 q = {p,p,p};

    //cnumpy<std::vector<std::vector<double>>> x = {v,v,v};
    //cnumpy<type4> x = {q,q,q};
    //cnumpy<type3> x = {p,p};
    //cnumpy<type0> x = {1,1,1,1};
    cnumpy<type2> x = {v,v,v,v};
    // x.push_back(a);
    print(2 + 3 * x * x * 2 + 4);

     //cnumpy<double> n = {1,2,3};
    //print(n);

 //   std::cout << n.size() << std::endl;
   // x.push_back(a);

   // print(n);

   //std::cout << "dim = " << getDim<std::decay<decltype(x)>::type>::dim() << "\n";
    //std::cout << "size: " << x.size() << std::endl;
    //std::cout << x[2][2] << std::endl;
      

    //std::cout << x[0] << std::endl;
//std::cout << x[1] << std::endl;
//std::cout << x[2] << std::endl;

    //print(a * a+ 2 + a + a * a * 2);

    //print(std::move(v)*std::move(v));
    //std::cout << std::rank< std::vector<std::vector<std::vector<double>>> >::value << std::endl;

}



















