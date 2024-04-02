#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cmath>
#include <random>

//#include <cstdlib>
//#include <type_traits>
//#include <string>
//#include <utility>

using Matrix2D = std::vector<std::vector<double>>;
using Colvec1D = std::vector<double>;

const Matrix2D matrix_error = Matrix2D(0,Colvec1D(0));


template<class T, class U>
class SimpleGnuplotOutput {
  std::string png_filename;
  int png_width, png_height;
  bool range_set_flag;
  T xrange_min, xrange_max;
  U yrange_min, yrange_max;
  std::string data_option;

  std::vector< std::vector< std::pair<T, U> > > data;

  bool _output(std::ostream& os){
    if(data.size()==0) return false;
    os << "set terminal png size " << png_width << "," << png_height << std::endl;
    os << "set output \"" << png_filename << "\"" << std::endl;
    os << "set size ratio 1" << std::endl;
    os << "set nokey" << std::endl;
    if(range_set_flag){
      os << "set xrange [" << xrange_min << ":" << xrange_max << "]" << std::endl;
      os << "set yrange [" << yrange_min << ":" << yrange_max << "]" << std::endl;
    }
    if(data.size()==1){
      os << "plot \"-\" using 1:2 " << data_option << std::endl;
      for(int i=0; i<data[0].size(); i++){
	os << data[0][i].first << "\t" << data[0][i].second << std::endl;
      }
      os << "e" << std::endl;
    }else{
      os << "plot ";
      for(int i=0; i<data.size(); i++){
	os << "\"-\"" << " using 1:2 " << data_option;
	if(i!=data.size()-1) os << ", ";
      }
      os << std::endl;
      for(int i=0; i<data.size(); i++){
	for(int j=0; j<data[i].size(); j++){
	  os << data[i][j].first << "\t" << data[i][j].second << std::endl;
	}
	os << "e" << std::endl;
      }
    }
    return true;
  }
public:
  SimpleGnuplotOutput(){ 
    png_filename = "output.png";
    png_width = png_height = 512;
    range_set_flag = false;
    data_option = "with lp pointtype 7";
  }

  void set_range(T xmin, T xmax, U ymin, U ymax){
    range_set_flag = true;
    xrange_min = xmin;
    xrange_max = xmax;
    yrange_min = ymin;
    yrange_max = ymax;
  }

  void set_data_option(const std::string& opt){
    data_option = opt;
  }

  void set_data(const std::vector< std::pair<T,U> >& d){
    data.push_back(d);
  }
  void clear_data(){
    data.clear();
  }
  bool output(){
    return _output(std::cout);
  }
  bool output(const std::string& filename){
    std::ofstream _ofs(filename.c_str());
    return _output(_ofs);
  }
};

class MatrixException : public std::runtime_error
{
public:
    MatrixException(): std::runtime_error("Error : Unmatch matrix size."){}

    MatrixException(std::string const& error)
    : std::runtime_error(error){}
};


#define TEMPLATE_VEC template<typename U \
    ,typename = typename std::enable_if< \
                                 std::is_same<std::remove_reference_t<U>, Matrix2D>::value \
                        >::type \
> \

#define TEMPLATE_VEC_VEC template<typename T, typename U \
                                ,typename = typename std::enable_if< \
                                (std::is_same<std::remove_reference_t<T>, Matrix2D>::value ) \
                                && (std::is_same<std::remove_reference_t<U>, Matrix2D>::value ) \
                        >::type \
> \

#define TEMPLATE_VAL_VEC template<typename T, typename U \
                           ,typename = typename std::enable_if< \
                                (std::is_same<T, double>::value || std::is_same<T, int>::value) \
                                && (std::is_same<std::remove_reference_t<U>, Matrix2D>::value ) \
                        >::type \
> \


#define TEMPLATE_VEC_VAL template<typename T, typename U \
            ,typename = typename std::enable_if< \
                                (std::is_same<std::remove_reference_t<T>, Matrix2D>::value ) \
                                && (std::is_same<U, int>::value || std::is_same<U, double>::value) \
                        >::type \
> \

void print(double t, bool end = true){
    std::cout << t;
    if(end) std::cout << std::endl;
}

void print(int t, bool end = true){
    std::cout << t;
    if(end) std::cout << std::endl;
}

void print(std::vector<double> &t, bool end = true){
    std::cout << "[";
    for(auto &x : t){
          std::cout << x;
          if (&x != &t.back()) std::cout << " ";
    }
   
    std::cout << "]";
    if(end) std::cout << std::endl;
}

void print(std::vector<std::vector<double>> &t){
    std::cout << "[";
    int i=0;
    for(auto &v : t){
        i++;
        print(v ,false);
        if(i == t.size()) std::cout << "]";
        std::cout << std::endl;
    }

} 




TEMPLATE_VEC_VEC
auto operator+(T&& x, U&& y){
    
    int x_row = x.size();
    int x_col = x[0].size();

    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res;

    try {
        if(x_row != y_row && x_col != y_col){
            if((x_row == 1 && x_col == 1) || (y_row == 1 && y_col == 1)){
             
            }else{
                throw MatrixException("+ -> Matrix Exception");
                exit;
            }        
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    if(x_row == y_row && x_col == y_col){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j<x_col ; ++j)
                res[i][j] =  x[i][j] + y[i][j];

    }else if(x_row == y_row && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j<y_col ; ++j)
               res[i][j] =  x[i][0] + y[i][j];

    }else if(x_row == y_row && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] + y[i][0];

    }else if(x_col == y_col && x_row == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)
                res[i][j] =  x[0][j] + y[i][j];

    }else if(x_col == y_col && y_row == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] + y[0][j];

    }else if(x_row == 1 && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)        
                res[i][j] =  x[0][0] + y[i][j];

    }else if(y_row == 1 && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] + y[0][0];

    }
    
    return res;
}


TEMPLATE_VAL_VEC
auto operator+(T x, U&& y){
    
    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res(y_row, Colvec1D(y_col));

    for(int i=0;i<y_row;++i){
        for(int j=0;j<y_col;++j){
            res[i][j] = x + y[i][j];
        }
    }

    return res;
}



TEMPLATE_VEC_VAL
auto operator+(T&& x, U y){
    
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row, Colvec1D(x_col));

    for(int i=0;i<x_row;++i){
        for(int j=0;j<x_col;++j){
            res[i][j] = x[i][j] + y;
        }
    }

    return res;
}



TEMPLATE_VEC_VEC
auto operator-(T&& x, U&& y){
    int x_row = x.size();
    int x_col = x[0].size();

    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res;

    try {
        if(x_row != y_row && x_col != y_col){
            if((x_row == 1 && x_col == 1) || (y_row == 1 && y_col == 1)){
             
            }else{
                throw MatrixException("- -> Matrix Exception");
                exit;
            }        
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    if(x_row == y_row && x_col == y_col){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j<x_col ; ++j)
                res[i][j] =  x[i][j] - y[i][j];

    }else if(x_row == y_row && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j<y_col ; ++j)
               res[i][j] =  x[i][0] - y[i][j];

    }else if(x_row == y_row && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[i][0];

    }else if(x_col == y_col && x_row == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)
                res[i][j] =  x[0][j] - y[i][j];

    }else if(x_col == y_col && y_row == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[0][j];

    }else if(x_row == 1 && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)        
                res[i][j] =  x[0][0] - y[i][j];

    }else if(y_row == 1 && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] - y[0][0];

    }
    
    return res;
}


TEMPLATE_VAL_VEC
auto operator-(T x, U&& y){

    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res(y_row, Colvec1D(y_col));

    for(int i=0;i<y_row;++i){
        for(int j=0;j<y_col;++j){
            res[i][j] = x - y[i][j];
        }
    }

    return res;
}


TEMPLATE_VEC_VAL
auto operator-(T&& x, U y){

    int x_row = x.size();
    int x_col = x[0].size();


    Matrix2D res(x_row, Colvec1D(x_col));

    for(int i=0;i<x_row;++i){
        for(int j=0;j<x_col;++j){
            res[i][j] = x[i][j] - y;
        }
    }

    return res;
}


TEMPLATE_VEC_VEC
auto operator*(T&& x, U&& y){ 
    int x_row = x.size();
    int x_col = x[0].size();

    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res;

    try {
        if(x_row != y_row && x_col != y_col){
            if((x_row == 1 && x_col == 1) || (y_row == 1 && y_col == 1)){
             
            }else{
                throw MatrixException("* -> Matrix Exception");
                exit;
            }        
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    if(x_row == y_row && x_col == y_col){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j<x_col ; ++j)
                res[i][j] =  x[i][j] * y[i][j];

    }else if(x_row == y_row && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j<y_col ; ++j)
               res[i][j] =  x[i][0] * y[i][j];

    }else if(x_row == y_row && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] * y[i][0];

    }else if(x_col == y_col && x_row == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)
                res[i][j] =  x[0][j] * y[i][j];

    }else if(x_col == y_col && y_row == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] * y[0][j];

    }else if(x_row == 1 && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)        
                res[i][j] =  x[0][0] * y[i][j];

    }else if(y_row == 1 && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] * y[0][0];

    }
    
    return res;

}



TEMPLATE_VEC_VAL 
auto operator*(T&& x, U y){

    //auto a = std::forward<T>(x);
    int x_row = x.size();
    int x_col = x[0].size();
    
    Matrix2D res(x_row, Colvec1D(x_col));
    
    for(int i= 0 ; i< x_row; ++i){
        for(int j=0; j< x_col;++j){
            res[i][j] = x[i][j] * y;
        }
    }

    return res;
} 



TEMPLATE_VAL_VEC 
auto operator*(T x, U&& y){
    int y_row = y.size();
    int y_col = y[0].size();
    
    Matrix2D res(y_row, Colvec1D(y_col));
    
    for(int i= 0 ; i< y_row; ++i){
        for(int j=0; j< y_col;++j){
            res[i][j] = x * y[i][j];
        }
    }

    return res;
} 



TEMPLATE_VEC_VEC
auto operator/(T&& x, U&& y){ 
    int x_row = x.size();
    int x_col = x[0].size();

    int y_row = y.size();
    int y_col = y[0].size();

    Matrix2D res;

    try {
        if(x_row != y_row && x_col != y_col){
            if((x_row == 1 && x_col == 1) || (y_row == 1 && y_col == 1)){
             
            }else{
                std::cerr << "[" << x_row << ", " << x_col << "]" << "/ [" << y_row << ", " << y_col << "]" << std::endl;
                throw MatrixException("/ -> Matrix Exception");
                exit;
            }        
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    if(x_row == y_row && x_col == y_col){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j<x_col ; ++j)
                res[i][j] =  x[i][j] / y[i][j];

    }else if(x_row == y_row && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j<y_col ; ++j)
               res[i][j] =  x[i][0] / y[i][j];

    }else if(x_row == y_row && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] / y[i][0];

    }else if(x_col == y_col && x_row == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)
                res[i][j] =  x[0][j] / y[i][j];

    }else if(x_col == y_col && y_row == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] / y[0][j];

    }else if(x_row == 1 && x_col == 1){
        res.resize(y_row, Colvec1D(y_col));
        for(int i=0;i< y_row;++i)
            for(int j=0;j< y_col ; ++j)        
                res[i][j] =  x[0][0] / y[i][j];

    }else if(y_row == 1 && y_col == 1){
        res.resize(x_row, Colvec1D(x_col));
        for(int i=0;i< x_row;++i)
            for(int j=0;j< x_col ; ++j)
                res[i][j] =  x[i][j] / y[0][0];

    }
    
    return res;

}


TEMPLATE_VEC_VAL
auto operator/(T&& x, U y){

    int x_row = x.size();
    int x_col = x[0].size();
    
    Matrix2D res(x_row, Colvec1D(x_col));
    
    for(int i= 0 ; i< x_row; ++i){
        for(int j=0; j< x_col;++j){
            res[i][j] = x[i][j] / y;
        }
    }

    return res;
} 


TEMPLATE_VAL_VEC
auto operator/(T x, U&& y){
    int y_row = y.size();
    int y_col = y[0].size();
    
    Matrix2D res(y_row, Colvec1D(y_col));
    
    for(int i= 0 ; i< y_row; ++i){
        for(int j=0; j< y_col;++j){
            res[i][j] = x / y[i][j];
        }
    }

    return res;
} 




TEMPLATE_VEC
auto sqrt(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x_row;++i){
        for(int j=0; j< x_col;++j){
            res[i][j] = sqrt(x[i][j]);
        }
    }

    return res;
}





TEMPLATE_VEC
auto T(U&& x){

    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_col, Colvec1D(x_row));

    for(int i=0;i<x_row;++i)
        for(int j=0; j<x_col;++j)
            res[j][i] = x[i][j];

    return res;

}


TEMPLATE_VEC_VEC
auto dot(T&& x, U&& y){
    
    int x_row = x.size();
    int x_col = x[0].size();
    int y_row = y.size();
    int y_col = y[0].size();

    try {
        if(x_col != y_row){
            std::cout << x_col << ", " << y_row << std::endl;
            throw MatrixException("dot -> Matrix Exception");
            exit;
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    Matrix2D res(x_row, Colvec1D(y_col));

    for(int i = 0; i < x_row; ++i){
        for(int j = 0; j < y_col; ++j){
            for(int k = 0; k < y_row; ++k){
                res[i][j] += x[i][k] * y[k][j];
            }
        }
    }

    return res;

}

// only support keepdims = True

TEMPLATE_VEC
auto sum(U &&x, int axis){
    int x_row = x.size();
    int x_col = x[0].size();
    
    Matrix2D res;

    if(axis == 0){
        res.resize(1, Colvec1D(x_col));

        for(int i=0; i<x_col; ++i)
            for(int j=0; j<x_row; ++j)
                res[0][i] += x[j][i];

        return res;

    }

    res.resize(x_row, Colvec1D(1));

    for(int j=0; j<x_row; ++j) 
        for(int i=0; i<x_col; ++i)
            res[j][0] += x[j][i];

    return res;

}


TEMPLATE_VEC
double sum(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();
    
    double res = 0.0;

    for(int i=0; i<x_col; ++i)
        for(int j=0; j<x_row; ++j)
            res += x[j][i];
     
    return res; 

}


TEMPLATE_VEC
auto average(U &&x, int axis){
    int x_row = x.size();
    int x_col = x[0].size();
    
    Matrix2D res;

    if(axis == 0){
        res = sum(x, 0) / x_row;
        return res;
    }
     
    res.resize(x_row, Colvec1D(1));
    res = sum(x, 1) / x_col;
        
    return res;

}


TEMPLATE_VEC
double average(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();
    
    double res = sum(x);

    double div = x_row * x_col; 
    
    return res/div; 
}


TEMPLATE_VEC
auto stddev(U &&x, int axis){
    
    Matrix2D res;

    if(axis == 0){
        auto ave = average(x,0); 
        auto z = x-ave; 
        auto ave2 = average(z*z,0);
        return res = sqrt(ave2);
    }
     
    auto ave = average(x,1); 
    auto z = x-ave; 
    auto ave2 = average(z*z,1);
            
    return res = res = sqrt(ave2);
}


TEMPLATE_VEC
double stddev(U&& x){
    
    double res = 0.0;
    double ave = average(x); 

    auto z = x-ave; 
    auto ave2 = average(z*z);
            
    return res  = sqrt(ave2);

}


TEMPLATE_VEC
auto exp(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = exp(x[i][j]);
        }
    }

    return res;
}

TEMPLATE_VEC
auto sigmoid(U&& x){
  
    return 1.0/(1.0 + exp(-1 * x));

}


TEMPLATE_VEC
auto log(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = log(x[i][j]);
        }
    }

    return res;
}

TEMPLATE_VEC
auto cos(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = cos(x[i][j]);
        }
    }

    return res;
}

TEMPLATE_VEC
auto sin(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = sin(x[i][j]);
        }
    }

    return res;
}

TEMPLATE_VEC
auto ReLu(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = x[i][j] > 0.0 ? x[i][j] : 0.0;
        }
    }

    return res;
}


TEMPLATE_VEC
auto Diff_ReLu(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    for(int i=0; i< x.size();++i){
        for(int j=0; j< x[0].size();++j){
            res[i][j] = x[i][j] > 0.0 ? 1.0 : 0.0;
        }
    }

    return res;
}

TEMPLATE_VEC
auto tanh(U&& x){
    return  (exp(x) - exp(-1 * x)) / (exp(x) + exp(-1 * x));
}

TEMPLATE_VEC
auto zeros_like(U&& x){
    int x_row = x.size();
    int x_col = x[0].size();

    Matrix2D res(x_row , Colvec1D(x_col));

    return res;
}

auto random_randn(int row, int col){
    Matrix2D res(row , Colvec1D(col));
    double sigma = 1.0;
    std::random_device seed;
    std::mt19937 engine(seed());
    std::normal_distribution<> generator(0.0, sigma);

    for(int i=0; i<row; ++i)
        for(int j=0; j<col; ++j)
            res[i][j] = generator(engine);

    return res;
}

auto zeros(int col){
    Matrix2D res(1, Colvec1D(col, 0.0));
    
    return res;
}


auto eye(int row){

    Matrix2D res(row , Colvec1D(row, 0.0));

    for(int i=0; i<row; ++i){
        res[i][i] = 1.0;
    }

    return res;
}



TEMPLATE_VEC_VEC
auto c_(T&& x, U&& y){
    
    int x_row = x.size();
    int x_col = x[0].size();
    int y_row = y.size();
    int y_col = y[0].size();

    try {
        if(x_row != y_row){
            std::cout << x_row << ", " << y_row << std::endl;
            throw MatrixException("c_ -> Matrix Exception");
            exit;
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    Matrix2D res(x_row, Colvec1D(x_col + y_col));

    for(int i=0; i<x_row ; ++i){
        for(int j=0; j<x_col ; ++j){
            res[i][j] = x[i][j];

        }
    }

    for(int i=0; i<y_row ; ++i){
        for(int j=0; j<y_col ; ++j){
            res[i][x_col + j] = y[i][j];

        }
    }

    return res;
}

TEMPLATE_VEC_VEC
auto r_(T&& x, U&& y){
    
    int x_row = x.size();
    int x_col = x[0].size();
    int y_row = y.size();
    int y_col = y[0].size();

    try {
        if(x_col != y_col){
            std::cout << x_col << ", " << y_col << std::endl;
            throw MatrixException("r_ -> Matrix Exception");
            exit;
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    Matrix2D res(x_row + y_row, Colvec1D(x_col));

    for(int i=0; i<x_row ; ++i){
        for(int j=0; j<x_col ; ++j){
            res[i][j] = x[i][j];

        }
    }

    for(int i=0; i<y_row ; ++i){
        for(int j=0; j<y_col ; ++j){
            res[x_row + i][j] = y[i][j];

        }
    }

    return res;
}

TEMPLATE_VEC
auto slice_row(U&& y, int row){

    int y_row = y.size();
    int y_col = y[0].size();

   try {
        if(row > y_row){
            std::cout << row << ", " << y_row << std::endl;
            throw MatrixException("slice_row -> Matrix Exception");
            exit;
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }
    
    Matrix2D res(1, Colvec1D(y_col));
    
    for(int i=0; i< y_col;++i){

        res[0][i] = y[row][i]; 
    }

    return res;
}

TEMPLATE_VEC
auto slice_col(U&& y, int col){
    int y_row = y.size();
    int y_col = y[0].size();

    try {
        if(col > y_col){
            std::cout << col << ", " << y_col << std::endl;
            throw MatrixException("slice_col -> Matrix Exception");
            exit;
        }
    } catch (const MatrixException &e) {
        std::cout << e.what() << std::endl;;
    }

    Matrix2D res(y_row, Colvec1D(1));
    for(int i=0; i< y_row; ++i){
        res[i][0] = y[i][col]; 
    }

    return res;
}
