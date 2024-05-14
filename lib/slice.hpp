#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <cassert>

std::vector<std::string> split(std::string &&str){
    std::vector<std::string> res;
    std::string s;   
    bool isString = false; 
    for(auto c : str){
        if(c == ':'){
            if(isString == true) res.emplace_back(s);
            res.emplace_back(std::string{':'});
            s.clear();
            isString = false;
            
        }else{
            assert(0x30 <= c && c <= 0x39);    
            isString = true;
            s += c;
        }
    }
    if(s != "") res.emplace_back(s);

    return res;
}

auto slice(std::vector<double> &&x, int a){
    return x[a];
}

auto slice(std::vector<double> &x, int a){
    return x[a];
}

auto slice(std::vector<double> &&x, const char *s){
    auto vec = split(s);
    std::vector<double> res;

    if(vec[0] == ":" && vec.size() == 1){         // :
        res = x;
    }else if(vec[0] == ":" && vec.size() == 2){   // :10
        int len = stoi(vec[1]);
        res.resize(len);
        for(int i=0; i<len; ++i){
            res[i] = x[i];
        }
    }else if(vec[1] == ":" && vec.size() == 2){   // 10:
        int len = stoi(vec[0]);
        res.resize(x.size()-len);
        for(int i=0, j=len; i<x.size()-len; ++i,++j){
            res[i] = x[j];
        }
    }else if(vec[1] == ":" && vec.size() == 3){
        int len1 = stoi(vec[0]);
        int len2 = stoi(vec[2]);
        res.resize(len2-len1);
        for(int i=0, j=len1; i<len2-len1; ++i,++j){
            res[i] = x[j];
        }
    }
    return res;

}


auto slice(std::vector<double> &x, const char *s){
   return slice(std::move(x), s);
}

auto slice(std::vector<std::vector<double>> &x){
    return x;
}

auto slice(std::vector<std::vector<double>> &&x){
    return x;
}

auto slice(std::vector<std::vector<double>> &x, int a){
    return x[a];
}

auto slice(std::vector<std::vector<double>> &&x, int a){
    return x[a];
}

auto slice(std::vector<std::vector<double>> &x, int a, int b){
    return x[a][b];
}

auto slice(std::vector<std::vector<double>> &&x, int a, int b){
    return x[a][b];
}

auto slice(std::vector<std::vector<double>> &&x, const char* s){
    auto vec = split(s);
    std::vector<std::vector<double>>  res;

    if(vec[0] == ":" && vec.size() == 1){         // :
        for(auto &v : x){
            res.emplace_back(v);
        }
    }else if(vec[0] == ":" && vec.size() == 2){   // :10
        int len = stoi(vec[1]);
        for(int i=0; i<len; ++i){
            res.emplace_back(x[i]);
        }

    }else if(vec[1] == ":" && vec.size() == 2){   // 10:
        int len = stoi(vec[0]);
        for(int i=len; i<x.size(); ++i){
            res.emplace_back(x[i]);
        }
    }else if(vec[1] == ":" && vec.size() == 3){
        int len1 = stoi(vec[0]);
        int len2 = stoi(vec[2]);
        for(int i=len1; i<len2; ++i){
            res.emplace_back(x[i]);
        }
    }
    return res;

}

auto slice(std::vector<std::vector<double>> &x, const char* s){
    return slice(std::move(x), s);
}


auto slice(std::vector<std::vector<double>> &&x, const char* s, int a){
    auto vec = split(s);
    std::vector<double>  res;

    if(vec[0] == ":" && vec.size() == 1){         // :
        for(auto &v : x){
            res.emplace_back(v[a]);
        }
    }else if(vec[0] == ":" && vec.size() == 2){   // :10
        int len = stoi(vec[1]);
        for(int i=0; i<len; ++i){
            res.emplace_back(x[i][a]);
        }

    }else if(vec[1] == ":" && vec.size() == 2){   // 10:
        int len = stoi(vec[0]);
        for(int i=len; i<x.size(); ++i){
            res.emplace_back(x[i][a]);
        }
    }else if(vec[1] == ":" && vec.size() == 3){
        int len1 = stoi(vec[0]);
        int len2 = stoi(vec[2]);
        for(int i=len1; i<len2; ++i){
            res.emplace_back(x[i][a]);
        }
    }
    return res;

}

auto slice(std::vector<std::vector<double>> &x, const char* s, int a){
    return slice(std::move(x), s, a);

}

auto slice(std::vector<std::vector<double>> &&x, int a ,const char* s){
    auto vec = split(s);
    std::vector<double>  res;

    if(vec[0] == ":" && vec.size() == 1){         // :
        res = x[a];

    }else if(vec[0] == ":" && vec.size() == 2){   // :10
        int len = stoi(vec[1]);
        for(int i=0; i<len; ++i){
            res.emplace_back(x[a][i]);
        }
    }else if(vec[1] == ":" && vec.size() == 2){   // 10:
        int len = stoi(vec[0]);
        for(int i=len; i<x.size(); ++i){
            res.emplace_back(x[a][i]);
        }
    }else if(vec[1] == ":" && vec.size() == 3){
        int len1 = stoi(vec[0]);
        int len2 = stoi(vec[2]);
        for(int i=len1; i<len2; ++i){
            res.emplace_back(x[a][i]);
        }
    }
    return res;

}

auto slice(std::vector<std::vector<double>> &x, int a ,const char* s){
    return slice(std::move(x), a, s);
}


auto slice(std::vector<std::vector<double>> &&x, const char* s ,const char* t){
    auto vec1 = split(s);
    auto vec2 = split(t);
    std::vector<std::vector<double>>  res;

    if(vec1[0] == ":" && vec1.size() == 1){             // :
        if(vec2[0] == ":" && vec2.size() == 1){         // :
            res = x;
        }else if(vec2[0] == ":" && vec2.size() == 2){   // :10
            int clen = stoi(vec2[1]);
           
            for(auto &v: x){
                std::vector<double> vec;
                for(int i=0; i<clen; ++i){
                   vec.emplace_back(v[i]);
                } 
                res.emplace_back(vec);
            }
        }else if(vec2[1] == ":" && vec2.size() == 2){   // 10:
            int clen = stoi(vec2[0]);
            for(auto &v: x){
                std::vector<double> vec;
                for(int i=clen; i<x.size(); ++i){
                   vec.emplace_back(v[i]);
                } 
                res.emplace_back(vec);
            }
            
        }else if(vec2[1] == ":" && vec2.size() == 3){
            int clen1 = stoi(vec2[0]);
            int clen2 = stoi(vec2[2]);

            for(auto &v: x){
                std::vector<double> vec;
                for(int i=clen1; i<clen2; ++i){
                   vec.emplace_back(v[i]);
                } 
                res.emplace_back(vec);
            }
        }
    }else if(vec1[0] == ":" && vec1.size() == 2){       // :10
        int rlen = stoi(vec1[1]);
        if(vec2[0] == ":" && vec2.size() == 1){         // :
            for(int i=0; i<rlen; ++i){
                res.emplace_back(x[i]);
            }

        }else if(vec2[0] == ":" && vec2.size() == 2){   // :10
            int clen = stoi(vec2[1]);
            for(int i=0; i<rlen; ++i){
                std::vector<double> vec;
                for(int j=0; j< clen; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }

        }else if(vec2[1] == ":" && vec2.size() == 2){   // 10:
            int clen = stoi(vec2[0]);
            for(int i=0; i< rlen; ++i){
                std::vector<double> vec;
                for(int j=clen; j< x[0].size(); ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }else if(vec2[1] == ":" && vec2.size() == 3){
            int clen1 = stoi(vec2[0]);
            int clen2 = stoi(vec2[2]);

            for(int i=0; i< rlen; ++i){
                std::vector<double> vec;
                for(int j=clen1; j< clen2; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }
    }else if(vec1[1] == ":" && vec1.size() == 2){   // 10:
        int rlen = stoi(vec1[0]);
        if(vec2[0] == ":" && vec2.size() == 1){         // :
            for(int i=rlen; i<x.size(); ++i){
                res.emplace_back(x[i]);
            }
        }else if(vec2[0] == ":" && vec2.size() == 2){   // :10
            int clen = stoi(vec2[1]);
            for(int i=rlen; i<x.size(); ++i){
                std::vector<double> vec;
                for(int j=0; j< clen; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }

        }else if(vec2[1] == ":" && vec2.size() == 2){   // 10:
            int clen = stoi(vec2[0]);
            for(int i=rlen; i< x.size(); ++i){
                std::vector<double> vec;
                for(int j=clen; j< x[0].size(); ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }else if(vec2[1] == ":" && vec2.size() == 3){
            int clen1 = stoi(vec2[0]);
            int clen2 = stoi(vec2[2]);

            for(int i=rlen; i< x.size(); ++i){
                std::vector<double> vec;
                for(int j=clen1; j< clen2; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }
    }else if(vec2[1] == ":" && vec2.size() == 3){        // 1:5
        int rlen1 = stoi(vec1[0]);
        int rlen2 = stoi(vec1[2]);
        if(vec2[0] == ":" && vec2.size() == 1){         // :
            for(int i=rlen1; i<rlen2; ++i){
                res.emplace_back(x[i]);
            }
        }else if(vec2[0] == ":" && vec2.size() == 2){   // :10
            int clen = stoi(vec2[1]);
            for(int i=rlen1; i<rlen2; ++i){
                std::vector<double> vec;
                for(int j=0; j< clen; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }else if(vec2[1] == ":" && vec2.size() == 2){   // 10:
            int clen = stoi(vec2[0]);

            for(int i=rlen1; i<rlen2; ++i){
                std::vector<double> vec;
                for(int j=clen; j< x[0].size(); ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }  
        }else if(vec2[1] == ":" && vec2.size() == 3){
            int clen1 = stoi(vec2[0]);
            int clen2 = stoi(vec2[2]);

            for(int i=rlen1; i<rlen2; ++i){
                std::vector<double> vec;
                for(int j=clen1; j< clen2; ++j){
                    vec.emplace_back(x[i][j]);
                }
                res.emplace_back(vec);
            }
        }
    }
    return res;
}

auto slice(std::vector<std::vector<double>> &x, const char* s ,const char* t){
    return slice(std::move(x), s, t);
}


template <typename T, class... Tail>
auto slice(std::vector<T> &&x, const char* s, Tail&&... tail){
    auto vec = split(s);
    if(vec[0] == ":" && vec.size() == 1){         // :
        std::vector<decltype(slice(x[0], std::forward<Tail>(tail)...))> res;
        for(auto &u : x){
            res.emplace_back(slice(u, std::forward<Tail>(tail)...));
        }
        return res;
        
    }else if(vec[0] == ":" && vec.size() == 2){   // :10
        int len = stoi(vec[1]);
        std::vector<decltype(slice(x[0], std::forward<Tail>(tail)...))> res;
        for(int i=0; i<len; ++i){
            res.emplace_back(slice(x[i], std::forward<Tail>(tail)...));
        }
        return res;
    }else if(vec[1] == ":" && vec.size() == 2){   // 10:
        int len = stoi(vec[0]);
        std::vector<decltype(slice(x[len], std::forward<Tail>(tail)...))> res;
        for(int i=len; i<x.size(); ++i){
            res.emplace_back(slice(x[i], std::forward<Tail>(tail)...));
        }
        return res;
    }else if(vec[1] == ":" && vec.size() == 3){
        int len1 = stoi(vec[0]);
        int len2 = stoi(vec[2]);
        std::vector<decltype(slice(x[len1], std::forward<Tail>(tail)...))> res;
        for(int i=len1; i<len2; ++i){
            res.emplace_back(slice(x[i], std::forward<Tail>(tail)...));
        }
        return res;
    }
}

template <typename T, class... Tail>
auto slice(std::vector<T> &x, const char* s, Tail&&... tail){
    return slice(std::move(x, s, std::forward<Tail>(tail)...));
}


template<typename T, class... Tail>
auto slice(std::vector<T> &&x, int a, Tail&&... tail){
    return slice(x[a], std::forward<Tail>(tail)...);
}


template<typename T, class... Tail>
auto slice(std::vector<T> &x, int a, Tail&&... tail){
    return slice(x[a], std::forward<Tail>(tail)...);
}


