#include "discreteobject.h"


DiscreteObject::~DiscreteObject(){
}

DiscreteObject::DiscreteObject(std::vector<double> n_B, std::vector<double> n_A, unsigned int n_k=0):
    B(n_B),
    A(n_A),
    k(n_k)
{
    U = std::deque<double>(20, 0);
    Y = std::deque<double>(20, 0);
}

DiscreteObject::DiscreteObject() : DiscreteObject(std::vector<double>(0), std::vector<double>(0)){}
DiscreteObject::DiscreteObject(ModelData md) : DiscreteObject(md.getB(), md.getA(), md.getK()){}

void DiscreteObject::setModel(ModelData md){
    setParameters(md.getB(), md.getA(), md.getK());
}

void DiscreteObject::setParameters(std::vector<double> n_B, std::vector<double> n_A, unsigned int n_k){
    B = n_B;
    A = n_A;
    k = n_k;
}

void DiscreteObject::reset(){
    U.clear();
    Y.clear();
    U = std::deque<double>(20, 0);
    Y = std::deque<double>(20, 0);
}

double DiscreteObject::simulate(double input){
    double out = 0.0;

    U.push_front(input);

    if(Y.size() >= A.size()-1){
        out -= std::inner_product(A.begin() + 1, A.end(), Y.begin(), 0.0);
    }else{
        out -= std::inner_product(Y.begin(), Y.end(), A.begin() + 1, 0.0);
    }

    std::deque<double>::iterator it = U.begin();
    it += k-1;
    if(U.size() >= B.size()+k-1){
        out += std::inner_product(B.begin(), B.end(), it, 0.0);
    }else if(U.size() > k-1){
        out += std::inner_product(it, U.end(), B.begin(), 0.0);
    }else{
        //do nothing
    }

    out /= A.at(0); //dzielimy y przez A[0] gdyby bylo rozne od 1

    Y.push_front(out);

    //usuwamy niepotrzebną historię (pozostawiamy jednek lekki zapas)
    int b = 5;
    if(Y.size() > A.size()-1 + b){
        Y.pop_back();
    }
    if(U.size() > B.size()+k-1 + b){
        U.pop_back();
    }
    return out;
}

void DiscreteObject::setU(std::deque<double> n_U){
    U = n_U;
}

void DiscreteObject::setY(std::deque<double> n_Y){
    Y = n_Y;
}
