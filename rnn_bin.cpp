// Categorize　Iris

#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "calc.h"
#include "matplotlib.h"
#include "iris.h"


class SimpleRNNLayer{
public:
    SimpleRNNLayer(int row, int col){
        w = random_randn(row, col)/ sqrt(row);
        v = random_randn(col, col)/ sqrt(col);
        b = zeros(col);

    }

    void forward(Matrix2D &x, Matrix2D &y_prev){
        auto u = dot(x, w) + dot(y_prev, v) + b;
        y = tanh(u);
    }

    void backward(Matrix2D &x, Matrix2D &y, Matrix2D &y_prev, Matrix2D &grad_y){
        auto delta = grad_y * ( 1- y *y);
        grad_w = grad_w + dot(T(x), delta);

        grad_v = grad_v + dot(T(y_prev), delta);

        grad_b = grad_b + sum(delta, 0);

        grad_x = dot(delta, T(w));
        grad_y_prev = dot(delta, T(v));
    }

    ~SimpleRNNLayer(){}

    void update(double eta){

        w = w - eta * grad_w;
        v = v - eta * grad_v;
        b = b - eta * grad_b;

    }
    
    void reset_sum_grad(){   
        grad_w = zeros_like(w);
        grad_v = zeros_like(v);
        grad_b = zeros_like(b);

    }


private:
    Matrix2D w;  
    Matrix2D v;
    Matrix2D b;

    Matrix2D y;

    Matrix2D grad_w;
    Matrix2D grad_v;
    Matrix2D grad_b;
    
    Matrix2D grad_x;
    Matrix2D grad_y_prev;



};



class RNNOutLayer{
public:

    RNNOutLayer(int row, int col){
        w = random_randn(row, col)/ sqrt(row);
        b = zeros(col);

    }

    void forward(Matrix2D &x){
        auto u = dot(x, w) + b;
        y = sigmoid(u);
    }

    void backward(Matrix2D &x, Matrix2D &y, Matrix2D &t){
        auto delta = (y -t) * y * (1-y);
        grad_w = grad_w + dot(T(x), delta);
        grad_b = grad_b + sum(delta, 0);
        grad_x = dot(delta, T(w));

    }

    void reset_sum_grad(){
        grad_w = zeros_like(w);
        grad_b = zeros_like(b);
    }

    void updata(double eta){
        w = w - eta * grad_w;
        b = b - eta * grad_b;

    }

private:
    Matrix2D w;  
    Matrix2D b;

    Matrix2D grad_w;  
    Matrix2D grad_b;
    Matrix2D grad_x;

    Matrix2D y;  



};


#define CURRENT_RBP(x) \
  __asm__("mov %%rbp, %0;" :"=r"(x) );

  #define CURRENT_RSP(x) \
  __asm__("mov %%rsp, %0;" :"=r"(x) );

std::string toBinary(int n) {
  std::string r;
  while (n != 0) {
    r += (n % 2 == 0 ? "0" : "1");
    n /= 2;
  }
  return r;
}

std::string padding8(std::string &s){
    unsigned long long bp;
    CURRENT_RBP(bp);
    std::cout << std::hex << bp << std::endl;

    unsigned long long sp;
    CURRENT_RSP(sp);
    std::cout << std::hex << sp << std::endl;

    if(s.size() < 8){
        while(s.size() != 8){
            s += "0";
        }
    }
    return s;
}

void addr(std::string &&s){
    std::cout << std::hex << &s << std::endl;

}


int main(){

    int a = 44;
    std::string aaa = toBinary(a);
    std::cout << std::hex << &aaa << std::endl;
    addr(padding8(aaa));

    std::vector<Matrix2D> input;
    Matrix2D u;
    u = Matrix2D(1, Colvec1D(2,0));
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);
    input.push_back(u);



}
