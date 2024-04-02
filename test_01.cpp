#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "calc.h"


class BaseLayer{
public:
    BaseLayer(){}

    ~BaseLayer(){}
private:

};



class MiddleLayer: public BaseLayer{
public:
    MiddleLayer(int row, int col){
        double sigma = 0.05;
        std::random_device seed;
        std::mt19937 engine(seed());
        std::normal_distribution<> generator(0.0, sigma);
        
        w.resize(row, Colvec1D(col));
        b.resize(1, Colvec1D(col));

        for(int i=0;i<row;++i)
            for(int j=0;j<col;++j)
                w[i][j] =  generator(engine);

        for(int i=0;i<col;++i)
                b[0][i] = generator(engine);

    }

    ~MiddleLayer(){
    }

    void forward(Matrix2D &in){
        x = in;
        Matrix2D u = dot(x,w) + b; 
        y = sigmoid(u);        
    }

    void backward(Matrix2D &grad_y){
        Matrix2D delta = grad_y * (1 - y) * y;
        grad_w = dot(T(x), delta);
        grad_b = sum(delta, 0);
        grad_x = dot(delta, T(w));

    }

    void update(double eta){
        w = w - eta * grad_w;
        b = b - eta * grad_b;

    }

    Matrix2D y;  // output
    Matrix2D grad_x;


private:
    
    Matrix2D x;  
    Matrix2D w;  
    Matrix2D b;


    Matrix2D grad_w;
    Matrix2D grad_b;

};

class OutputLayer : public BaseLayer{
public:
    OutputLayer(int row, int col){
        double sigma = 0.05;
        std::random_device seed;
        std::mt19937 engine(seed());
        std::normal_distribution<> generator(0.0, sigma);
        
        w.resize(row, Colvec1D(col));
        b.resize(1, Colvec1D(col));

        for(int i=0;i<row;++i)
            for(int j=0;j<col;++j)
                w[i][j] =  generator(engine);

        for(int i=0;i<col;++i)
                b[0][i] = generator(engine);


    }

    ~OutputLayer(){

        
    }


 
    void forward(Matrix2D &in){
        x = in;                       //  1 * row
        Matrix2D u = dot(x,w) + b;    //  1 * col
        y = u;
    }

    void backward(Matrix2D &t){
        Matrix2D delta = y - t;
        grad_w = dot(T(x), delta);
        grad_b = sum(delta, 0);
        grad_x = dot(delta, T(w));

    }

    void update(double eta){
        w = w - eta * grad_w;
        b = b - eta * grad_b;

    }

    Matrix2D y;  // output
    Matrix2D grad_x;

private:
    Matrix2D x;  
    Matrix2D w;  
    Matrix2D b;


    Matrix2D grad_w;
    Matrix2D grad_b;


};


int main(){
  

    double eta = 0.1;

    MiddleLayer m(1,3);
    OutputLayer o(3,1);

    Matrix2D in_data(1);
    double d = 0.0;

    std::vector<int> indexes;
    for(int i=0; d < 2*M_PI; ++i){
        in_data[0].push_back(d);
        indexes.push_back(i);
        d+=0.1;
    }

    Matrix2D t_data = sin(in_data);

#if 1

    in_data = (in_data - M_PI) / M_PI;

    Matrix2D in(1, Colvec1D(1));
    Matrix2D t(1, Colvec1D(1));

    for(int i=0; i<2000; ++i){

        std::mt19937_64 get_rand_mt; 
        std::shuffle( indexes.begin(), indexes.end(), get_rand_mt );

        for(auto index : indexes){
            in[0][0]= in_data[0][index];
            t[0][0]= t_data[0][index];

            m.forward(in);
            o.forward(m.y);

            o.backward(t);
            m.backward(o.grad_x);

            m.update(eta);
            o.update(eta);

        }
    }

        std::vector<std::pair<double, double>> result;

    for(int i=0; i<in_data[0].size(); ++i){
        in[0][0]= in_data[0][i];

        m.forward(in);
        o.forward(m.y);

        double bbb =  in[0][0];
        double y = o.y[0][0];
        
        result.push_back(std::make_pair(bbb, y));

    }

    SimpleGnuplotOutput<double, double> go;
    go.set_range(-1, 1, -1, 1);
    go.set_data(result); //データをセット
    go.output("out.plt"); //ファイルに出力

   
#endif
   return 0;
}
