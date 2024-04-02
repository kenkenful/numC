#include <iostream>
#include <vector>
#include <type_traits>

using Matrix2D = std::vector<std::vector<double>>;
using Colvec1D = std::vector<double>;

template < typename T >
struct is_vector : std::false_type{};

template < typename T >
struct is_vector<std::vector<T>> : std::true_type {};

template < typename T >
constexpr bool is_vec = is_vector<T>::value;

template < typename T >
struct is_vector_vector : std::false_type{};

template < typename T >
struct is_vector_vector<std::vector<std::vector<T>>> : std::true_type {};

template < typename T >
constexpr bool is_vecvec = is_vector_vector<T>::value;






template<typename T, typename U
    ,typename = typename std::enable_if<
                                (std::is_same<std::remove_reference_t<T>, Matrix2D>::value
                                || std::is_same<std::remove_reference_t<T>, Colvec1D>::value)
                                && (std::is_same<std::remove_reference_t<U>, Matrix2D>::value
                                || std::is_same<std::remove_reference_t<U>, Colvec1D>::value)
                        >::type
>
auto operator+(T&& x, U&& y){
    //auto a = std::forward<T>(x);
    //auto b = std::forward<U>(y);
    
    int a_row;
    int a_col;

    int b_row;
    int b_col;

    Matrix2D res;
    Matrix2D a;
    Matrix2D b;

    if constexpr(is_vec<std::remove_reference_t<T>>){
        a_row = 1;
        a_col = x.size();
        
        a.resize(a_row, Colvec1D(a_col));
        for(int i=0; i<a_col;++i) a[0][i] = x[i];

    }else if constexpr(is_vec_vec<std::remove_reference_t<T>>){
        a_row = x.size();
        a_col = x[0].size();

        a.resize(a_row, Colvec1D(a_col));
        a = x;
    }

    if constexpr(is_vec<std::remove_reference_t<U>>){
        b_row = 1;
        b_col = y.size();
        
        b.resize(b_row, Colvec1D(b_col));
        for(int i=0; i<b_col;++i) b[0][i] = y[i];

    }else if constexpr(is_vec_vec<std::remove_reference_t<U>>){
        b_row = y.size();
        b_col = y[0].size();

        b.resize(b_row, Colvec1D(b_col));
        b = y;
    }

    res.resize(b_row, Colvec1D(b_col));

    for(int i=0;i<a_row;++i){
        for(int j=0;j<a_col;++j){
            res[i][j] = a[i][j] + b[i][j];
        }
    }

    return res;
}


template <typename T>
void testFunc(T&& arg){
    std::cout << arg << std::endl;
}

template <>
void testFunc(std::vector<double> &&arg){
    //std::cout << (arg ? "yes":"no") << std::endl;
}

#define CURRENT_RBP(x) \
  __asm__("mov %%rbp, %0;" \
            :"=r"(x) \
          );


template<typename T>
auto getvecvec(T&& t){
    unsigned long reg;
    CURRENT_RBP(reg);

    std::cout << "base: " << reg << std::endl;

    std::vector<std::vector<double>> a;
    std::cout << "local a: " << std::hex << &a << std::endl;

    std::cout << "local t: " << std::hex << &t << std::endl;


    if constexpr (is_vec_vec<std::remove_reference_t<T>>){
        std::cout << "vec vec" << std::endl;
        return t;


    }else if constexpr (is_vec<std::remove_reference_t<T>>){
    
        a.resize(1, std::vector<double>(t.size()));
        std::cout << "vec" << std::endl;
        //a[0] = t; 
        return a;

    }
        
}

int main(){

    std::vector<std::vector<double>> a = {{1,1,1}};
    std::vector<double> b = {3,2,3};


    std::cout << std::hex << &b << std::endl;

    auto v = getvecvec(b);
    std::cout << std::hex << &v << std::endl;
   

    std::cout << std::hex << &a << std::endl;

    auto t = getvecvec(a);
    std::cout << std::hex << &t << std::endl;
   


}

