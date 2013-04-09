#ifndef CONTROLLERAPZP1_H
#define CONTROLLERAPZP1_H

#include "controllerrst.h"
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "identification/arxidentification.h"

class ControllerAPZP1 : public ControllerRST
{
public:
    ControllerAPZP1();
    ControllerAPZP1(std::vector<double> n_Am, std::vector<double> n_Bm);

    void clearParameters();
    double simulate(double);
    void reset();

private:

    int dB; /**< stopien wielomianu A (do identyfikacji ARX) */
    int dA; /**< stopien wielomianu B4 (do identyfikacji ARX) */
    int k; /**< opoznienie obiektu (do identyfikacji ARX) */
    double l; /**< wspolczynnik wazenia lambda (do identyfikacji ARX) */

    int dF; /**< stopien wielomianu A (do identyfikacji ARX) */
    int dG; /**< stopien wielomianu B4 (do identyfikacji ARX) */

    std::vector<double> Am;
    std::vector<double> Bm;
    ARXIdentification arx1;
    ARXIdentification arx2;
};

#endif // CONTROLLERAPZP1_H
