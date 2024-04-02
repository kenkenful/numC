// Categorize　Iris

#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "calc.h"
#include "matplotlib.h"
#include "iris.h"


class BaseLayer{
public:
    BaseLayer(int row, int col){
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

    ~BaseLayer(){}

    void update(double eta){
        w = w - eta * grad_w;
        b = b - eta * grad_b;
    }

protected:
    Matrix2D w;  
    Matrix2D b;


    Matrix2D grad_w;
    Matrix2D grad_b;


};



class MiddleLayer: public BaseLayer{
public:
    MiddleLayer(int row, int col): BaseLayer(row,col){
        
    }

    ~MiddleLayer(){
    }

    void forward(Matrix2D &in){
        x = in;
        Matrix2D u = dot(x,w) + b; 

        // ReLU
        y = ReLu(u);
    }

    void backward(Matrix2D &grad_y){
        Matrix2D delta = grad_y * Diff_ReLu(y);
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

};

class OutputLayer : public BaseLayer{
public:
    OutputLayer(int row, int col): BaseLayer(row,col){

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

};



int main(){

    
    std::vector<int> indexes;

    int epoch = 3000;

    double eta = 0.01;

    MiddleLayer m1(4,25);
    MiddleLayer m2(25,25);
    OutputLayer o(25,3);

    Matrix2D train_input;
    Matrix2D train_output;

    Matrix2D test_input;
    Matrix2D test_output;

    // create train and test data
    for(int i=0; i<input_data.size();++i){
        if(i%2 == 0 ){
            train_input.push_back(input_data[i]);
            train_output.push_back(correct_data[i]);
        }else{
            test_input.push_back(input_data[i]);
            test_output.push_back(correct_data[i]);    
        }        
            
    }

    int batch_size = 8;
    int n_batch = train_input.size() / batch_size;

    // cretae index
    for(int i=0; i < train_input.size();++i)
        indexes.push_back(i);

    matplotlib g;

	// initialize
	g.open();

	// set drawing range
	g.screen(0.0, 0.0, 3000, 1.5);

    for(int j=0; j < epoch; ++j  ){

        // shuffle index
        std::mt19937_64 get_rand_mt; 
        std::shuffle(indexes.begin(), indexes.end(), get_rand_mt );

        int index = 0;
        for(int i=1; i <= n_batch; ++i){
            Matrix2D in;
            Matrix2D t;

            // create mini batch
            for(; index < batch_size * i ; ++index){
                in.push_back(train_input[indexes[index]]);    // [8 , 4]
                t.push_back(train_output[indexes[index]]);   // [8 , 3]
            }

            m1.forward(in);     
            m2.forward(m1.y);
            o.forward(m2.y);

            o.backward(t);
            m2.backward(o.grad_x);
            m1.backward(m2.grad_x);

            m1.update(eta);
            m2.update(eta);
            o.update(eta);

        }

        if(j %10 == 0){
            m1.forward(test_input);
            m2.forward(m1.y);
            o.forward(m2.y);

            //print(o.y);

            double error = -1 * sum( test_output * log(o.y + 1e-7) )/test_output.size();
            //std::cout << j << ": " << error <<std::endl;
             g.point(j, error, "red", "s=10");
        }


    }

    
    getchar();

	//  drfinishawing
	g.close();

   return 0;
}
