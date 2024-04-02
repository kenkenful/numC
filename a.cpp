#include "calc.h"
#include <random>

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

#include <algorithm>


int main(){
    std::vector<std::vector<double>> vec(1);
    vec[0].push_back(3);
    std::cout << vec[0][0];
#if 0


    double eta = 0.1;

    MiddleLayer m(1,5);
    OutputLayer o(5,1);

    Matrix2D in = {{3}};
    Matrix2D t = {{10}};

    for(int i=0; i<100; ++i){
        m.forward(in);
        o.forward(m.y);

        for(auto &vec : o.y)
            for(auto v : vec)
                std::cout << v << std::endl;

        o.backward(t);
        m.backward(o.grad_x);

        m.update(eta);
        o.update(eta);
    }

    SimpleGnuplotOutput<double, double> go;
    go.set_range(0, 10, -1, 1);
    std::vector<std::pair<double, double>> E_stock;

    double sigma = 0.5;
        std::random_device seed;
        std::mt19937 engine(seed());
        std::normal_distribution<> generator(0.0, sigma);

    for(int i=0; i<100; ++i){
        double t = 0.1 * i;
         E_stock.push_back(std::make_pair(t, sin(t) + generator(engine)));

    }

    go.set_data(E_stock); //データをセット
    go.output("out.plt"); //ファイルに出力
        


#endif
   

  



   return 0;
}

#if 0


int main(){


    //Matrix2D a = {{6,3,5}};
    //Matrix2D b = {{9,2,3},{10,2,3},{5,2,3}};
      ///  Matrix2D c = {{9,2}};


    //auto z = dot(c, (a + b/4 * b ))*c;

    //print(z);



    SimpleGnuplotOutput<int, double> go;
    go.set_range(0, 1000, 0, 1);

    int N = 4;
    Matrix2D x = {{0.0 ,0.0},          // 4 * 2
                  {0.0 ,1.0},
                  {1.0 ,0.0},
                  {1.0 ,1.0}};
    
    Matrix2D y = {{0.0},{0.0},{0.0},{1.0}};   // 4 * 1 
    
    Matrix2D w =  {{0.0},{1.0}};                // 2 * 1 
    Matrix2D b =  {{0.0},{0.0},{0.0},{0.0}};    // 4 * 1 

    double eta = 0.2;
    std::vector<std::pair<int, double>> E_stock;

    for(int i=0; i<1000; ++i){
    
        Matrix2D y_hat = sigmoid(dot(x,w) + b);     // 4 * 1 
    
        double E = sum(-1*(y * log(y_hat) + (1 - y) * log(1 - y_hat)))/N;
        E_stock.push_back(std::make_pair(i, E));
    
        Matrix2D dw = sum((x * (y_hat - y)), 0)/N;   // 1 * 2
        Matrix2D db = sum((y_hat - y) , 1) /N;       // 4 * 1

        Matrix2D temp = T(db); 

        w = w - eta * T(dw); 

        b = b - eta * db;  
    
   }

    go.set_data(E_stock); //データをセット
    go.output("out.plt"); //ファイルに出力


}

#endif


