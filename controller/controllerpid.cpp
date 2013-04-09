#include "controllerpid.h"

ControllerPID::ControllerPID(){
    ControllerPID(0,0,0);
}

ControllerPID::ControllerPID(double n_P, double n_I, double n_D):
    kr(n_P),
    Ti(n_I),
    Td(n_D),
    lastI(0),
    lastD(0),
    lastWU(0),
    windUpEnabled(false)
{
}

ControllerPID::~ControllerPID(){
}

//double ControllerPID::simulateI(){
//    double sI = I * sPeriod;

//    if(U.size() > 1 && I != 0){
//        lastI = lastI + sI * ( P * U[1] + lastWU );
//    }else{
//        lastI = 0;
//    }
//    return lastI;
//}

//double ControllerPID::simulateD(){
//    double N = 100;
//    double sD = D*sPeriod;
//    if(U.size() > 1){
//        lastD = sD/(sD+N)*lastD + P*N*sD/(sD+N)*(U[0] - U[1]);
//    }else{
//        lastD = sD/(sD+N)*lastD;
//    }
//    return lastD;
//}

double ControllerPID::simulate(double y){
    double e = sp - y;

    // simulate I:
    lastI = lastI + e;
    double outI = lastI / Ti * sPeriod;

    // simulate P:
    double out = (e + outI) * kr;

    // anty windup
    windUpEnabled = false;
    if (windUpEnabled) {
        double out2 = out < windUpMin ? windUpMin : (out > windUpMax ? windUpMax : out);
        lastWU = out2-out;
        out = out2;
    } else {
        lastWU = 0;
    }

    return out;
}

void ControllerPID::reset(){
    lastI = 0;
    lastD = 0;
    lastWU = 0;
}

void ControllerPID::setParameters(double n_P, double n_I, double n_D){
    kr = n_P;
    Ti = n_I;
    Td = n_D;
}

void ControllerPID::setWindUp(bool n_enabled, double n_min, double n_max){
    windUpEnabled = n_enabled;
    windUpMin = n_min;
    windUpMax = n_max;
}
