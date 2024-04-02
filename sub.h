#pragma once 

#include <vector>
#include "cnumpy.h"


auto operator-(std::vector<double>&& x, double y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i]-y;
    }

    return res;
}

template<typename T>
auto operator-(std::vector<T>&& x, double y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) - y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(std::vector<T>& x, double y){ 
    return std::move(x) - y;

}






auto operator-(double x, std::vector<double>&& y){ 
    std::vector<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x - y[i];
    }

    return res;
}

template<typename T>
auto operator-(double x, std::vector<T>&& y){ 
    std::vector<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x - std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(double x, std::vector<T>& y){ 
    return x - std::move(y);

}


auto operator-(std::vector<double>&& x, std::vector<double>&& y){ 
    std::vector<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i] - y[i];
    }

    return res;
}

template<typename T>
auto operator-(std::vector<T>&& x, std::vector<T>&& y){ 
    std::vector<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) - std::forward<T>(y[i]);
    }

    return res;
}

// left left interface
template<typename T>
auto operator-(std::vector<T>& x, std::vector<T>& y){ 
    return std::move(x) - std::move(y);

}

// right left interface
template<typename T>
auto operator-(std::vector<T>&& x, std::vector<T>& y){ 
    return std::forward<std::vector<T>>(x) - std::move(y);

}

// left right interface
template<typename T>
auto operator-(std::vector<T>& x, std::vector<T>&& y){ 
    return std::move(x) - std::forward<std::vector<T>>(y);

}


auto operator-(cnumpy<double>&& x, double y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size(); ++i){
      res[i] = x[i] - y;
    }

    return res;
}

template<typename T>
auto operator-(cnumpy<T>&& x, double y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) - y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(cnumpy<T>& x, double y){ 
    return std::move(x) - y;

}




auto operator-(double x, cnumpy<double>&& y){ 
    cnumpy<double> res(y.size());
    for(int i=0; i< y.size(); ++i){
      res[i] = x - y[i];
    }

    return res;
}

template<typename T>
auto operator-(double x, cnumpy<T>&& y){ 
    cnumpy<T> res(y.size());
   
    for(int i=0; i<y.size(); ++i){
      res[i] = x - std::forward<T>(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(double x, cnumpy<T>& y){ 
    return x - std::move(y);

}

////////////////////////////////

auto operator-(cnumpy<double>&& x, cnumpy<double>&& y){ 
    cnumpy<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i] - y[i];
    }

    return res;
}

template<typename T>
auto operator-(cnumpy<T>&& x, cnumpy<T>&& y){ 
    cnumpy<T> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = std::forward<T>(x[i]) - std::forward<T>(y[i]);
    }

    return res;
}

// left left interface
template<typename T>
auto operator-(cnumpy<T>& x, cnumpy<T>& y){ 
    return std::move(x) - std::move(y);

}

// right left interface
template<typename T>
auto operator-(cnumpy<T>&& x, cnumpy<T>& y){ 
    return std::forward<cnumpy<T>>(x) - std::move(y);

}

// left right interface
template<typename T>
auto operator-(cnumpy<T>& x, cnumpy<T>&& y){ 
    return std::move(x) - std::forward<cnumpy<T>>(y);

}