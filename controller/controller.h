#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <map>

/**
 * @brief Klasa podstawowa Regulatora, dziedziczy po klasie obiektu dyskretnego
 *
 */
class Controller
{
public:

    /**
     * @brief Konstruktor
     *
     */
    Controller();
    /**
     * @brief Destruktor
     *
     */
    ~Controller();

    double virtual simulate(double) = 0;
    void reset();
    double setSP(double);
    double setSamplePeriod(double);

protected:
    double sp;
    double sPeriod;
};
#endif // CONTROLLER_H
