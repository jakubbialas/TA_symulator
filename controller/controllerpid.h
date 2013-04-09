#ifndef CONTROLLERPID_H
#define CONTROLLERPID_H

#include "controller.h"
#include <iostream>
#include <deque>

/**
 * @brief Klasa Regulatora typu PID dziedziczy po klasie Regulaora
 * Na razie jest to tylko wzów klasy, sam regulator nie został jeszcze zaimplementowany!
 * TODO: implementacja regulatora PID
 */
class ControllerPID : public Controller
{
protected:
    double kr;
    double Ti;
    double Td;

    double lastI, lastD, lastWU;
public:
    ControllerPID();
    ~ControllerPID();
    ControllerPID(double, double, double);

    double simulate(double);
    void reset();
    void setParameters(double, double, double);
    void setWindUp(bool, double, double);

private:
    bool windUpEnabled;
    double windUpMin;
    double windUpMax;

    void actualize();
};

#endif // CONTROLLERPID_H
