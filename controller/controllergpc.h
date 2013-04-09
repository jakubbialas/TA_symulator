#ifndef CONTROLLERGPC_H
#define CONTROLLERGPC_H

#include "controller.h"
#include "identification/modelidentification.h"
#include "object/modeldata.h"
#include "object/discreteobject.h"
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

//#include <boost/numeric/bindings/umfpack/umfpack.hpp>
//#include <boost/numeric/bindings/traits/ublas_vector.hpp>
//#include <boost/numeric/bindings/traits/ublas_sparse.hpp>
//#include <umfpack.h>
#include <boost/numeric/ublas/io.hpp>

//#include <umfpack.h>

/**
 * @brief Regulator GPC
 *
 */
class ControllerGPC : public Controller
{
public:

    ControllerGPC();
    ControllerGPC(double, double, double, ModelIdentification*);
    void setParameters(double, double, double, ModelIdentification*);
    double simulate(double);
    void reset();

private:
    ModelIdentification *ident; /**< TODO */

    int H; /**< Horyzont predykcji */
    int L; /**< Horyzont sterowac */
    double p; /**< parametr ro */

    std::deque<double> W;
    std::deque<double> U;
    std::deque<double> Y;
};

#endif // CONTROLLERGPC_H
