#include "controllerapzp1.h"

ControllerAPZP1::ControllerAPZP1()
{
    ControllerAPZP1(std::vector<double>(0), std::vector<double>(0));
}

ControllerAPZP1::ControllerAPZP1(std::vector<double> n_Am, std::vector<double> n_Bm):
    Am(n_Am),
    Bm(n_Bm)
{
    k = 1;
    l = 0.9;

    dA = 1;
    dB = 0;

    int dAm = Am.size() - 1;
    int dA0 = 0;

    dG = ((dA - 1) > dAm + dA0 - k) ? dA - 1 : dAm + dA0 - k;
    dF = k - 1;

    int dR = dB + dF;
    int dS = dG;

    arx2 = ARXIdentification(dS, dR, l);
}

void ControllerAPZP1::reset(){
    ControllerRST::reset();
}
double ControllerAPZP1::simulate(double y){

    // model identification:
    double gamma = inner_product(Am.begin(), Am.end(), Y.begin(), 0.0);
    ModelData mdSR = arx2.identify(Y[k], U[k], gamma);

    //std::cout << "yug " << Y[k] << ";" << U[k] << ";" << gamma << std::endl;

    std::vector<double> R = mdSR.getA(); // R
    std::vector<double> S = mdSR.getB(); // S
    std::vector<double> T = Bm;

    //std::cout << "RST " << R << S << T << std::endl;

    // set new R, S, and T
    ControllerRST::setParameters(R, S, T);

    // continue simulation:
    double u = ControllerRST::simulate(y);

    return u;
}
