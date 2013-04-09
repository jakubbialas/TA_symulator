#include "modeldata.h"

ModelData::ModelData():
    B(std::vector<double>(0)),
    A(std::vector<double>(0)),
    k(0),
    t(0){}

ModelData::ModelData(std::vector<double> n_B, std::vector<double> n_A, unsigned int n_k, unsigned int n_t):
    B(n_B),
    A(n_A),
    k(n_k),
    t(n_t){}

ModelData::~ModelData(){
}

void ModelData::setB(std::vector<double> n_B){
    B = n_B;
}

std::vector<double> ModelData::getB() const{
    return B;
}

void ModelData::setA(std::vector<double> n_A){
    A = n_A;
}

std::vector<double> ModelData::getA() const{
    return A;
}

void ModelData::setK(unsigned int n_k){
    k = n_k;
}

unsigned int ModelData::getK() const{
    return k;
}

void ModelData::setT(unsigned int n_t){
    t = n_t;
}

unsigned int ModelData::getT() const{
    return t;
}

std::ostream& operator << (std::ostream &stream, const ModelData &md){
    stream << "[ ";
    stream << "t: " << md.getT() << ", ";
    stream << "A: " << md.getA() << ", ";
    stream << "B: " << md.getB() << ", ";
    stream << "k: " << md.getK() << ", ";
    stream << "]";
    return stream;
}
