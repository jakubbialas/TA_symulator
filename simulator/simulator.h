#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <vector>

#include "plant.h"
#include "controller/controller.h"

class Simulator
{
public:
    Simulator();

    void virtual init(std::string control_name, int setPointVector) = 0; // abstract method init objective and controller
    void simulate();
    void setOutputFile(std::string);
    double virtual simulateController(double) = 0;

protected:
    AdaptiveTechniques::Plant* objective;
    Controller* controller;

    std::string filePath;
    double sampleTime;

    std::vector<double> sp;
    int spDuration;

    void setSP(double);
};

#endif // SIMULATOR_H
