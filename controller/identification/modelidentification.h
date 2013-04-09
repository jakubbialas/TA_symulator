#ifndef MODELIDENTIFICATION_H
#define MODELIDENTIFICATION_H

#include <vector>
#include <math.h>
#include "../object/modeldata.h"

class ModelIdentification
{
public:
    ModelIdentification();

    void setSampleTime(double);
    ModelData identify(double, double, double);

private:
    double sampleTime;
    double temp;
    double temp_w;
};

#endif // MODELIDENTIFICATION_H
