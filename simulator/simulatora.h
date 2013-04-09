#ifndef SIMULATORA_H
#define SIMULATORA_H

#include "simulator.h"
#include "controller/controllerpid.h"
#include "controller/controllerapzp1.h"
#include "controller/identification/arxidentification.h"
#include "controller/gainschedulingpid.h"
#include "controller/identification/modelidentification.h"
#include "controller/controllergpc.h"

class SimulatorA : public Simulator
{
public:
    SimulatorA();
    void init(std::string control_name, int setPointVector);
    void initObjective();
    void initGPC();
    void initSetPoint(int);
    double simulateController(double);

private:
    double last_y;
    double last_u;
    double alfa_y;
    double alfa_u;
};

#endif // SIMULATORA_H
