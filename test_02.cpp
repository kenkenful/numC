
// learning sin wave 

#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "calc.h"
#include "matplotlib.h"


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
                w[i][j] = generator(engine);

        for(int i=0;i<col;++i)
                b[0][i] = generator(engine);


    }

    ~OutputLayer(){

        
    }


 
    void forward(Matrix2D &in){
        x = in;                       //  1 * row
        Matrix2D u = dot(x,w) + b;    //  1 * col
        y = exp(u)/sum(exp(u), 1);

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
    
    matplotlib g;

	// initialize
	g.open();

	// set drawing range
	g.screen(-1, -1, 1, 1);


    double eta = 0.1;

    MiddleLayer m(2,6);
    OutputLayer o(6,2);

    Matrix2D in;
    Matrix2D t;

    
    // create teacher data

    double d = -1.0;
    int index = 0;
    std::vector<int> indexes;
    std::vector<Matrix2D> input;
    std::vector<Matrix2D> ans;

   
    std::vector<double> errors;

    for(int i=0; i<21; ++i){
        for(int j=0; j<21; ++j){
            indexes.push_back(index++);
            double x = -1.0 + 0.1*i;
            double y = -1.0 + 0.1*j;

            //std::cout << x << ":" <<  y  << std::endl;

            input.push_back({{x, y}});
            if(y < sin(M_PI*x))
                ans.push_back({{0,1}});  // lower
            else
                ans.push_back({{1,0}});  // upper
        }
    }

    int data_num = input.size();

    for(int i=0; i<300; ++i){

        double error = 0.0;
        std::mt19937_64 get_rand_mt; 
        std::shuffle( indexes.begin(), indexes.end(), get_rand_mt );

        for(auto index : indexes){
            in = input[index];
            t = ans[index];

            m.forward(in);
            o.forward(m.y);

            o.backward(t);
            m.backward(o.grad_x);

            m.update(eta);
            o.update(eta);

       
            error += -1* sum(t * log( o.y + 1e-7)); // cross emtropy
        }

        errors.push_back(error);

    }

    for(auto v : errors)
        std::cout <<  v/data_num << std::endl;


    for(auto &vec: input){
           m.forward(vec);
           o.forward(m.y);

            if(vec[0][1] < sin(M_PI*vec[0][0]))
                g.point(vec[0][0], vec[0][1], "red", "s=10");
            else
                g.point(vec[0][0], vec[0][1], "blue", "s=10");
          

    }

    getchar();

	//  drfinishawing
	g.close();

   return 0;
}
