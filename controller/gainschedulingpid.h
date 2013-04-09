#ifndef GAINSHEDULINGPID_H
#define GAINSHEDULINGPID_H

#include "controllerpid.h"
#include <math.h>

class GainSchedulingPID : public ControllerPID
{
public:
    GainSchedulingPID();

    double simulate(double);
};

#endif // GAINSHEDULINGPID_H
