#ifndef MODELDATA_H
#define MODELDATA_H

#include <vector>
#include <ostream>
#include "tool.h"

/**
 * @brief Klasa przechowujaca parametru obiektu dyskretnego
 *
 */
class ModelData
{
private:
    std::vector<double> B;  /**< Wielomian B */
    std::vector<double> A;  /**< Wielomian A */
    unsigned int k;         /**< Parametr k */
    unsigned int t;         /**< Czas przełączenia parametrow(nie stacjonarnść) */

public:
    /**
     * @brief Konstruktor
     *
     */
    ModelData();

    /**
     * @brief
     *
     * @param std::vector<double> B
     * @param std::vector<double> A
     * @param unsigned int k
     * @param unsigned int t
     */
    ModelData(std::vector<double> B, std::vector<double> A, unsigned int k, unsigned int t=0);

    /**
     * @brief Destruktor;
     *
     */
    ~ModelData();

    /**
     * @brief funkcja ustawia wielomian B
     *
     * @param std::vector<double> wielomian B
     */
    void setB(std::vector<double>);

    /**
     * @brief funkcja zwraca wielomian B
     *
     */
    std::vector<double> getB() const;

    /**
     * @brief funkcja ustawia wielomian A
     *
     * @param std::vector<double> wielomian A
     */
    void setA(std::vector<double>);

    /**
     * @brief funkcja zwraca wielomian A
     *
     */
    std::vector<double> getA() const;

    /**
     * @brief funkcja ustawia parametr k
     *
     * @param int parametr k
     */
    void setK(unsigned int);

    /**
     * @brief funkcja zwraca parametr k
     *
     */
    unsigned int getK() const;

    /**
     * @brief funkcja ustawia czas przełaczenia t
     *
     * @param int czas przełączenia t
     */
    void setT(unsigned int);

    /**
     * @brief funkcja zwraca czas przełaczenia t
     *
     */
    unsigned int getT() const;
};

#endif // MODELDATA_H

/**
 * @brief nadpisanie operatora strumienia zapisujacego dane z obiektu ModelData do strumienia std::ostream
 *
 * @param stream obiekt std::ostream
 * @param md obiekt z którego dane sa zapisywane
 */
std::ostream& operator << (std::ostream &stream, const ModelData &md);
