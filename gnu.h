#pragma once

#include <iostream>
#include <fstream>
#include <vector>
//#include <cstdlib>
//#include <string>
//#include <utility>


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

