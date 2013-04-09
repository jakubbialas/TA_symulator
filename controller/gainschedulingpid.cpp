#include "gainschedulingpid.h"

GainSchedulingPID::GainSchedulingPID()
{
}

double GainSchedulingPID::simulate(double y){
    double w = sp;

    double y0 = w;

    double eps = 0.8;
    double omega = 0.5;

    double tgalfa = 4.2687;
    double kv = 0.4336;

    double T = ( 2*M_PI* pow(y0, 5) )/( tgalfa*tgalfa * pow(kv, 6) );
    double k = 1;

    double kr = (2*eps*omega*T-1)/k;
    double Ti = (2*eps*omega*T-1)/(omega*omega*T);

//    std::cout << T << "; " << kr << "; " << Ti << "\n";

    if (kr < 0) kr = 0;
    if (kr > 10) kr = 10;
    if (Ti < 1) Ti = 1;
    if (Ti > 10) Ti = 10;
    //return w;

    ControllerPID::setParameters(kr, Ti, 0);
    return ControllerPID::simulate(y);
}
