#include "controllerrst.h"

ControllerRST::ControllerRST()
{
    ControllerRST(std::vector<double>(0), std::vector<double>(0), std::vector<double>(0));
}

ControllerRST::ControllerRST(std::vector<double> n_R, std::vector<double> n_S, std::vector<double> n_T):
    R(n_R),
    S(n_S),
    T(n_T),
    W(20, 0),
    Y(20, 0),
    U(20, 0)
{
}

void ControllerRST::setParameters(std::vector<double> n_R, std::vector<double> n_S, std::vector<double> n_T){
    R = n_R;
    S = n_S;
    T = n_T;
}

double ControllerRST::simulate(double y){
    double w = sp;

    W.push_front(w);
    Y.push_front(y);

    double out = 0.0;

    if(Y.size() >= S.size()){
        out -= std::inner_product(S.begin(), S.end(), Y.begin(), 0.0);
    }else{
        out -= std::inner_product(Y.begin(), Y.end(), S.begin(), 0.0);
    }

    if(W.size() >= T.size()){
        out += std::inner_product(T.begin(), T.end(), W.begin(), 0.0);
    }else{
        out += std::inner_product(W.begin(), W.end(), T.begin(), 0.0);
    }

    if(U.size() >= R.size() - 1){
        out -= std::inner_product(R.begin() + 1, R.end(), U.begin(), 0.0);
    }else{
        out -= std::inner_product(U.begin(), U.end(), R.begin() + 1, 0.0);
    }

    out /= R.at(0);

    if (out < 0) {
        out = 0;
    } else if (out > 20) {
        out = 20;
    }

    U.push_front(out);

    //usuwamy niepotrzebną historię (pozostawiamy jednek lekki zapas)
    int b = 10;
    if(Y.size() > S.size() + b){
        Y.pop_back();
    }
    if(W.size() > T.size() + b){
        W.pop_back();
    }
    if(U.size() > R.size() + b){
        U.pop_back();
    }

    return out;
}


void ControllerRST::reset(){
    R.clear();
    S.clear();
    T.clear();
    W.clear();
    Y.clear();
    U.clear();
    W = std::deque<double>(20, 0);
    Y = std::deque<double>(20, 0);
    U = std::deque<double>(20, 0);
}
