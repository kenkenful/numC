
#pragma once

#include <vector>

//  スカラー　1次元
auto dot(double t, std::vector<double> &&u){
    std::vector<double> res(u.size());

    for(int i=0; i<u.size(); ++i){
        res[i] = t * u[i];
    }

    return res;
}

auto dot(double t, std::vector<double> &u){
    return dot(t, std::move(u));

}

//  1次元 スカラー　
auto dot(std::vector<double> &&t, double u){
    std::vector<double> res(t.size());

    for(int i=0; i<t.size(); ++i){
        res[i] = t[i] * u;
    }

    return res;
}

auto dot(std::vector<double> &t, double u){
    return dot(std::move(t), u);
}

//  スカラー　2次元
auto dot(double t, std::vector<std::vector<double>> &&u){
    std::vector<std::vector<double>> res(u.size(), std::vector<double>(u[0].size()));

    for(int i=0; i<u.size(); ++i){
        for(int j=0; j< u[0].size(); ++j)
        res[i][j] = t * u[i][j];
    }

    return res;
}

auto dot(double t, std::vector<std::vector<double>> &u){

    return dot(t, std::move(u));
}

//  2次元 スカラー
auto dot(std::vector<std::vector<double>> &&t, double u){
    std::vector<std::vector<double>> res(t.size(), std::vector<double>(t[0].size()));

    for(int i=0; i<t.size(); ++i){
        for(int j=0; j< t[0].size(); ++j)
        res[i][j] = t[i][j] * u;
    }

    return res;
}

auto dot(std::vector<std::vector<double>> &t, double u){
    return dot(std::move(t), u);
}

//  1次元 1次元 内積
auto dot(std::vector<double> &&t, std::vector<double> &&u){
    double res;

    for(int i=0; i<t.size(); ++i){
        res += t[i] * u[i];
    }
    return res;
}

auto dot(std::vector<double> &t, std::vector<double> &u){
    return dot(std::move(t), std::move(u));

}

auto dot(std::vector<double> &t, std::vector<double> &&u){
    return dot(std::move(t), std::move(u));

}


auto dot(std::vector<double> &&t, std::vector<double> &u){
    return dot(std::move(t), std::move(u));

}


#if 0  //  2次元 1次元は定義されていない
auto dot(std::vector<std::vector<double>> &&t, std::vector<double> &&u){
    std::vector<std::vector<double>> res(t.size(), std::vector<double>(u.size()));

    for(int i=0; i<t.size();++i){
        for(int j=0; j<u.size();++j){
            res[i][j] = t[i][0] * u[j];
        }
    }

    return res;
}
#endif

auto dot(std::vector<double> &&t, std::vector<std::vector<double>> &&u){
    std::vector<double> res(u[0].size());

    for(int i=0; i<u[0].size() ;++i){
        for(int j=0; j< t.size(); ++j){
            res[i] += t[j] * u[j][i];
        }
    }

    return res;

    
}

//  1次元 2次元の行列積
auto dot(std::vector<double> &t, std::vector<std::vector<double>> &u){
    return dot(std::move(t), std::move(u));
     
}

auto dot(std::vector<double> &t, std::vector<std::vector<double>> &&u){
    return dot(std::move(t), std::move(u));
     
}

auto dot(std::vector<double> &&t, std::vector<std::vector<double>> &u){
    return dot(std::move(t), std::move(u));
     
}

//  2次元 2次元の行列積
auto dot(std::vector<std::vector<double>>&& t, std::vector<std::vector<double>>&& u){

    std::vector<std::vector<double>> res(t.size(), std::vector<double>(u[0].size()));

    for(int i = 0; i < t.size(); ++i){
        for(int j = 0; j < u[0].size(); ++j){
            for(int k = 0; k < u.size(); ++k){
                res[i][j] += t[i][k] * u[k][j];
            }
        }
    }

    return res;

}

auto dot(std::vector<std::vector<double>>&& t, std::vector<std::vector<double>>& u){
    return dot(std::move(t), std::move(u));
}

auto dot(std::vector<std::vector<double>>& t, std::vector<std::vector<double>>&& u){
    return dot(std::move(t), std::move(u));
}

auto dot(std::vector<std::vector<double>>& t, std::vector<std::vector<double>>& u){
    return dot(std::move(t), std::move(u));
}


// N次元 , ２次元
template <typename T>
auto dot(std::vector<std::vector<T>>&& x, std::vector<std::vector<double>>&& y){ 

    std::vector<std::vector<T>> res(x.size());
    for(int i=0; i< x.size();++i){
      res[i] = dot(std::move(x[i]),std::move(y));
    }
    return res;
}

template <typename T>
auto dot(std::vector<std::vector<T>>& x, std::vector<std::vector<double>>&& y){ 
    return dot(std::move(x),std::move(y));
}

template <typename T>
auto dot(std::vector<std::vector<T>>&& x, std::vector<std::vector<double>>& y){ 
    return dot(std::move(x),std::move(y));
}

template <typename T>
auto dot(std::vector<std::vector<T>>& x, std::vector<std::vector<double>>& y){ 
    return dot(std::move(x),std::move(y));
}


// 2次元 , N次元
template <typename T>
auto dot(std::vector<std::vector<double>>&& x, std::vector<std::vector<T>>&& y){ 

    std::vector<std::vector<T>> res(y.size());
    for(int i=0; i< y.size();++i){
      res[i] = dot(std::move(x),std::move(y[i]));
    }
    return res;
}


template <typename T>
auto dot(std::vector<std::vector<double>>& x, std::vector<std::vector<T>>&& y){ 
    return dot(std::move(x),std::move(y));
}


template <typename T>
auto dot(std::vector<std::vector<double>>&& x, std::vector<std::vector<T>>& y){ 
    return dot(std::move(x),std::move(y));
}


template <typename T>
auto dot(std::vector<std::vector<double>>& x, std::vector<std::vector<T>>& y){ 
    return dot(std::move(x),std::move(y));
}

// N次元 , N次元
template<typename T>
auto dot(std::vector<std::vector<T>>&& x, std::vector<std::vector<T>>&& y){ 

    std::vector<std::vector<T>> res(x.size());
   
    for(int i=0; i<x.size(); ++i){
      res[i] = dot(std::move(x[i]),std::move(y[i]));
    }

    return res;
}

template<typename T>
auto dot(std::vector<std::vector<T>>& x, std::vector<std::vector<T>>&& y){ 
    return dot(std::move(x),std::move(y));
}

template<typename T>
auto dot(std::vector<std::vector<T>>&& x, std::vector<std::vector<T>>& y){ 
    return dot(std::move(x),std::move(y));
}


template<typename T>
auto dot(std::vector<std::vector<T>>& x, std::vector<std::vector<T>>& y){ 
    return dot(std::move(x),std::move(y));
}
