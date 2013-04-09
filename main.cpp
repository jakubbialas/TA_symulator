#include "simulator/simulator.h"
#include "simulator/simulatora.h"

int main()
{
    Simulator *s = new SimulatorA();
    s->init("GPC", 1);
    s->setOutputFile("data.csv");
    s->simulate();

    return 0;
}

