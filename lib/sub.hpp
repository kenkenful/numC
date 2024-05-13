#pragma once 

#include <vector>
#include <cassert>
#include "meta.hpp"


//  1次元　０次元　original function
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
      //res[i] = std::forward<T>(x[i]) + y;
      res[i] = std::move(x[i]) - y;
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(std::vector<T>& x, double y){ 
    return std::move(x) - y;

}

////////////////////////////////

// ０次元　１次元　original function
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
      //res[i] = x + std::forward<T>(y[i]);
      res[i] = x - std::move(y[i]);
    }

    return res;
}

// left value interface
template<typename T>
auto operator-(double x, std::vector<T>& y){ 
    return x - std::move(y);

}

////////////////////////////////


//  1次元 , 1次元    original function
auto operator-(std::vector<double>&& x, std::vector<double>&& y){ 
    assert(x.size() == y.size());
    std::vector<double> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = x[i] - y[i];
    }

    return res;
}

auto operator-(std::vector<double>& x, std::vector<double>&& y){ 

    return std::move(x) - std::move(y);
}

auto operator-(std::vector<double>&& x, std::vector<double>& y){ 

    return std::move(x) - std::move(y);
}

auto operator-(std::vector<double>& x, std::vector<double>& y){ 

    return std::move(x) - std::move(y);
}


// 　N次元　1次元
template<typename T>
auto operator-(std::vector<T>&& x, std::vector<double>&& y){ 
    std::vector<T> res(x.size());
    for(int i=0; i< x.size();++i){
      //res[i] = std::forward<T>(x[i]) + std::forward<std::vector<double>>(y);
      res[i] = std::move(x[i]) - std::move(y);
    }

    return res;
}


template<typename T>
auto operator-(std::vector<T>& x, std::vector<double>&& y){ 

    //return std::move(x) + std::forward<std::vector<double>>(y);;
        return std::move(x) - std::move(y);

}

template<typename T>
auto operator-(std::vector<T>&& x, std::vector<double>& y){ 
  
    //return std::forward<std::vector<T>>(x) + std::move(y);
        return std::move(x) - std::move(y);

}

template<typename T>
auto operator-(std::vector<T>& x, std::vector<double>& y){ 

    return std::move(x) - std::move(y);
}


// 1次元　N次元
template<typename T>
auto operator-(std::vector<double>&& x, std::vector<T>&& y){ 
    std::vector<T> res(y.size());
    for(int i=0; i< y.size();++i){
      //res[i] =  std::forward<std::vector<double>>(x) + std::forward<T>(y[i]) ;
      res[i] = std::move(x) - std::move(y[i]) ;
    }

    return res;
}


template<typename T>
auto operator-(std::vector<double>& x, std::vector<T>&& y){ 
 
  //return std::move(x) + std::forward<std::vector<T>>(y);
  return std::move(x) - std::move(y);

}

template<typename T>
auto operator-(std::vector<double>&& x, std::vector<T>& y){ 
  //return std::forward<std::vector<double>>(x) + std::move(y) ;
  return std::move(x) - std::move(y);

}


template<typename T>
auto operator-(std::vector<double>& x, std::vector<T>& y){ 

    return std::move(x) - std::move(y);
}



// ２次元 , ２次元　　　original function
auto operator-(std::vector<std::vector<double>>&& x, std::vector<std::vector<double>>&& y){ 
    //std::cout << "22" << std::endl;

    int x_row = x.size();
    int x_col = x[0].size();

    int y_row = y.size();
    int y_col = y[0].size();

    if(x_row == 1 || y_row == 1){
        assert(x_col == y_col);
    }if(x_col == 1 || y_col){
        assert(x_row == y_row);
    }else{
        assert(x_col == y_col);
        assert(x_row == y_row);
    }

    std::vector<std::vector<double>> res;

     if(x_row == y_row && x_col == y_col){
        res.resize(x_row, std::vector<double>(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j<x_col ; ++j)
                res[i][j] =  x[i][j] - y[i][j];

    }else if(x_row == y_row && x_col == 1){
        res.resize(y_row, std::vector<double>(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j<y_col ; ++j)
               res[i][j] =  x[i][0] - y[i][j];

    }else if(x_row == y_row && y_col == 1){
        res.resize(x_row, std::vector<double>(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[i][0];

    }else if(x_col == y_col && x_row == 1){
        res.resize(y_row, std::vector<double>(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)
                res[i][j] =  x[0][j] - y[i][j];

    }else if(x_col == y_col && y_row == 1){
        res.resize(x_row, std::vector<double>(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[0][j];

    }else if(x_row == 1 && x_col == 1){
        res.resize(y_row, std::vector<double>(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)        
                res[i][j] =  x[0][0] - y[i][j];

    }else if(y_row == 1 && y_col == 1){
        res.resize(x_row, std::vector<double>(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[0][0];

    }

    return res;
}

auto operator-(std::vector<std::vector<double>>& x, std::vector<std::vector<double>>&& y){ 
    return std::move(x) - std::move(y);
}

auto operator-(std::vector<std::vector<double>>&& x, std::vector<std::vector<double>>& y){ 
    return std::move(x) - std::move(y);
}

auto operator-(std::vector<std::vector<double>>& x, std::vector<std::vector<double>>& y){ 
    return std::move(x) - std::move(y);
}



// N次元 , ２次元
template <typename T>
auto operator-(std::vector<std::vector<T>>&& x, std::vector<std::vector<double>>&& y){ 
    //std::cout << "N2" << std::endl;

    std::vector<std::vector<T>> res(x.size());
    for(int i=0; i< x.size();++i){
      //res[i] = std::forward<std::vector<T>>(x[i]) + std::forward<std::vector<std::vector<double>>>(y);
      res[i] = std::move(x[i]) - std::move(y);
    }

    return res;

}


// N次元 , ２次元
template <typename T>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<double>>&& y){ 

    //return std::move(x) + std::forward<std::vector<std::vector<double>>>(y);
    return std::move(x) - std::move(y);
}

// N次元 , ２次元
template <typename T>
auto operator-(std::vector<std::vector<T>>&& x, std::vector<std::vector<double>>& y){ 

    //return std::forward<std::vector<std::vector<T>>>(x) + std::move(y);
    return std::move(x) - std::move(y);
}

// N次元 , ２次元
template <typename T>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<double>>& y){ 

    return std::move(x) - std::move(y);

}

// 2次元 , N次元
template <typename T>
auto operator-(std::vector<std::vector<double>>&& x, std::vector<std::vector<T>>&& y){ 
    //std::cout << "2N" << std::endl;

    std::vector<std::vector<T>> res(y.size());
    for(int i=0; i< y.size();++i){
      //res[i] = std::forward<std::vector<std::vector<double>>>(x) + std::forward<std::vector<T>>(y[i]);
      res[i] = std::move(x) - std::move(y[i]);
    }
    return res;
}


// 2次元 , N次元
template <typename T>
auto operator-(std::vector<std::vector<double>>& x, std::vector<std::vector<T>>&& y){ 

    //return std::move(x) + std::forward<std::vector<std::vector<T>>>(y);
    return std::move(x) - std::move(y);
}

// 2次元 , N次元
template <typename T>
auto operator-(std::vector<std::vector<double>>&& x, std::vector<std::vector<T>>& y){ 
    
    //return std::forward<std::vector<std::vector<double>>>(x) + std::move(y);
    return std::move(x) - std::move(y);
}

// 2次元 , N次元
template <typename T>
auto operator-(std::vector<std::vector<double>>& x, std::vector<std::vector<T>>& y){ 
    
    return std::move(x) - std::move(y);
}


// N次元 , N次元
template<typename T>
auto operator-(std::vector<std::vector<T>>&& x, std::vector<std::vector<T>>&& y){ 
    //std::cout << "NN" << std::endl;

    std::vector<std::vector<T>> res(x.size());
    for(int i=0; i<x.size(); ++i){
      //res[i] = std::forward<std::vector<T>>(x[i]) + std::forward<std::vector<T>>(y[i]);
      res[i] = std::move(x[i]) - std::move(y[i]);
    }
    return res;
}

template<typename T>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<T>>&& y){
    //return std::move(x) + std::forward<std::vector<std::vector<T>>>(y);
    return std::move(x) - std::move(y);
}

template<typename T>
auto operator-(std::vector<std::vector<T>>&& x, std::vector<std::vector<T>>& y){
    //return std::forward<std::vector<std::vector<T>>>(x) + std::move(y);
    return std::move(x) - std::move(y);
}

template<typename T>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<T>>& y){
    return std::move(x) - std::move(y);
}


//   N次元　M次元
template<typename T, typename U>
auto operator-(std::vector<std::vector<T>>&& x,  std::vector<std::vector<U>>&& y){ 
    //std::cout << "MN" << std::endl;
    if constexpr (getDim<std::remove_reference_t<T>>::dim() >= getDim<std::remove_reference_t<U>>::dim()){
        std::vector<std::vector<T>> res(x.size());
        for(int i=0; i< x.size();++i){
            //res[i] = std::forward<std::vector<T>>(x[i]) +  std::forward<std::vector<std::vector<U>>>(y);
            res[i] = std::move(x[i]) -  std::move(y);
        }
        return res;
    }else{
        std::vector<std::vector<U>> res(y.size());
        for(int i=0; i< y.size();++i){
            res[i] = x - y[i];
        }
        return res;
    }
}

//   N次元　M次元
template<typename T, typename U>
auto operator-(std::vector<std::vector<T>>&& x, std::vector<std::vector<U>>& y){
    //return std::forward<std::vector<std::vector<T>>>(x) + std::move(y);
    return std::move(x) - std::move(y);
} 

//   N次元　M次元
template<typename T, typename U>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<U>>&& y){
    //return std::move(x) + std::forward<std::vector<std::vector<U>>>(y);
    return std::move(x) - std::move(y);
} 

//   N次元　M次元
template<typename T, typename U>
auto operator-(std::vector<std::vector<T>>& x, std::vector<std::vector<U>>& y){
    return std::move(x) - std::move(y);

} 



