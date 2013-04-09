#ifndef ARXIDENTIFICATION_H
#define ARXIDENTIFICATION_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <controller/object/modeldata.h>
#include <vector>
#include <deque>
#include <numeric>
#include <algorithm>


/**
 * @brief Klasa słurząca do identyfikacji obiektu ARX
 *
 */
class ARXIdentification
{
public:
/**
 * @brief konstruktor domyślny
 *
 */
    ARXIdentification();
/**
 * @brief konstruktor
 *
 * @param n_dB
 * @param n_dA
 * @param n_k
 * @param n_l
 */
    ARXIdentification(int n_dB, int n_dA, double n_l);
    /**
     * @brief kolejny krok identyfikacji
     *
     * @param in sygnal wchodzacy do identyfikowanego obiektu
     * @param out sygnal wychodzący z identyfikowanego obiektu
     */
    ModelData identify(double in, double out, double gamma = 0);

    boost::numeric::ublas::matrix<double> invert(
            boost::numeric::ublas::matrix<double> Q);

    double getLambda();
    /**
     * @brief funkcja ustawia parametr lambda
     *
     * @param double
     */
    void setLambda(double);

    void reset();

private:
    int dB; /**< stopien wielomianu B */
    int dA; /**< stopien wielomianu A */
    double lambda; /**< wspólczynnik wazenia */

    std::vector<double> B;
    std::vector<double> A;

    boost::numeric::ublas::matrix<double> covarMatrix; /**< macierz kowariancji */

    std::deque<double> inQueue; /**< wartosci wejsciowe */
    std::deque<double> outQueue; /**< wartosci wyjsciowe */


    boost::numeric::ublas::matrix<double> theta;
    boost::numeric::ublas::matrix<double> phi;
    std::vector<double> l_B;
    std::vector<double> l_A;
    boost::numeric::ublas::matrix<double> temp1;
    boost::numeric::ublas::matrix<double> temp3;
    boost::numeric::ublas::matrix<double> temp4;
    boost::numeric::ublas::matrix<double> temp5;
    boost::numeric::ublas::matrix<double> v_K;
    std::vector<double> n_B;
    std::vector<double> n_A;
};

#endif // ARXIDENTIFICATION_H
