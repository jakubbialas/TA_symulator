#include "controller.h"

Controller::Controller(){
}

Controller::~Controller(){
}

void Controller::reset(){}

double Controller::setSP(double n_sp){
    sp = n_sp;
}

double Controller::setSamplePeriod(double n_sPeriod){
    sPeriod = n_sPeriod;
}
