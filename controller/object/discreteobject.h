#ifndef DISCRETEOBJECT_H
#define DISCRETEOBJECT_H

#include "modeldata.h"
#include <cstdlib>
#include <numeric>

/**
 * @brief Klasa dziedziczaca po ObjectSISO, implementuje obiekt typu ARX
 *
 */
class DiscreteObject
{
protected:
    std::vector<double> B; /** wielomian B */
    std::vector<double> A; /** wielomian A */
    int k;                 /** opoznienie wejscia */

protected:
    std::deque<double> U;  /** kolejka wymuszeń */
    std::deque<double> Y;  /** kolejka stanu (poprzednie wartości) */

public:
    DiscreteObject();
    ~DiscreteObject();
    DiscreteObject(std::vector<double> B, std::vector<double> A, unsigned int k);
    DiscreteObject(ModelData md);

    void setModel(ModelData);
    void setParameters(std::vector<double> B, std::vector<double> A, unsigned int k);

    void reset();
    double simulate(double input);

    void setU(std::deque<double>);
    void setY(std::deque<double>);
};

#endif // DISCRETEOBJECT_H
