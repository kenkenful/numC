

#include "slice.h"
#include "trans.hpp"
#include "print.h"
#include "meta.h"
#include "dot.hpp"


int main(){


  using type0 = double;
  using type1 = std::vector<double>;
  using type2 = std::vector<std::vector<double>>;
  using type3 = std::vector<std::vector<std::vector<double>>>;
  using type4 = std::vector<std::vector<std::vector<std::vector<double>>>>;
  using type5 = std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>>;

  type1 a = {1,2,3};
  type1 b = {4,5,6};
  type1 c = {7,8,9};
  
  type2 v = {a,b,c};
   type3 r = {v, v,v};


  type2 v1 = {a};
  type2 v2 = {{1},{2},{3}};

 
  type4 q = {r,r};
  type4 p = {r};

  type5 z = {p,p};

  print(dot(r,v));

  //vector<3>::type ans = r;

  //std::cout << ch<int>::num << std::endl;

  //std::cout << GetCharNum<5, char ,int, char,char ,char >::value() << std::endl;

  //print(slice(std::move(v),1, ' '));

  //print(p);
  //std::cout << "--------------" <<std::endl;
  //print(T(p));
 // std::cout << "--------------" <<std::endl;
  //print(swap(std::move(p),2));




  //print(r);
  //std::cout << std::endl;
  //print(T(std::move(r)));

  
  //slice(std::move(r),' ', ' ', 1);

 // print(100+ a + r+ type4({r,r,r})+r + v+ 3+ type4({r,r,r}) + a + 4);
  //std::cout << slice(std::move(r),' ', ' ', 1) << std::endl; 
  //print( std::move(v) + p + std::move(p)  + v2 + r +  a + z + std::mve(a)+ p +  std::move(z) + std::move(p) + z + std::move(a) +7 +a + v + v + a + 5 + 5  + a + r + std::move(r)) ;

}