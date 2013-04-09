#ifndef CONTROLLERRST_H
#define CONTROLLERRST_H

#include "controller.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>

class ControllerRST : public Controller
{
public:
    ControllerRST();
    ControllerRST(std::vector<double>, std::vector<double>, std::vector<double>);
    void setParameters(std::vector<double>, std::vector<double>, std::vector<double>);

    void clearParameters();

    double simulate(double);
    void reset();

private:
    std::vector<double> R;
    std::vector<double> S;
    std::vector<double> T;

protected:
    std::deque<double> W;
    std::deque<double> U;
    std::deque<double> Y;
};

#endif // CONTROLLERRST_H
