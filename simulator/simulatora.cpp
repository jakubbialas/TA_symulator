#include "simulatora.h"

SimulatorA::SimulatorA()
{
    sampleTime = 0.01;
}

void SimulatorA::init(std::string control_name, int setPointVector) {
    std::cout << "SimulatorA::init\n";
    initObjective();
    initSetPoint(setPointVector);
    if (control_name.compare("gpc")) {
        initGPC();
    } else {
        throw "Unsupported controller";
    }
}

void SimulatorA::initSetPoint(int n) {
    std::cout << "SimulatorA::initSetPoint: " << n << "\n";

    double s1, s2;

    switch (n) {
        case 1:
            for (double i=0.1; i<=0.8; i+=0.1) {
                sp.push_back(i);
            }
            for (double i=0.7; i>=0.1; i-=0.1) {
                sp.push_back(i);
            }
            break;
        case 2:
            s1 = 0.2; s2 = 0.3;
            break;
        case 3:
            s1 = 0.4; s2 = 0.5;
            break;
        case 4:
            s1 = 0.6; s2 = 0.7;
            break;
        default:
            sp.push_back(0);
    }
    if (n > 1) {
        for (int i=0; i<3; i++) {
            sp.push_back(s1);
            sp.push_back(s2);
        }
    }
    spDuration = 10/sampleTime;
}

void SimulatorA::initObjective() {
    std::cout << "SimulatorA::initObjective\n";
    // obiekt:
    std::ostringstream strs;
    strs << sampleTime;
    std::string str = strs.str();

    objective = new AdaptiveTechniques::Plant();

    objective->setParameter("samplePeriod", str);
    objective->setParameter("disturbances", "0.5");
}

void SimulatorA::initGPC() {
    std::cout << "SimulatorA::initGPC\n";
    // zmienne:
    last_y = 0;
    last_u = 0;
    alfa_y = 0.13/sampleTime;
    alfa_u = 0.18/sampleTime;

    // identyfikacja:
    ModelIdentification * ident = new ModelIdentification();
    ident->setSampleTime(sampleTime);

    // parametry regulatora:
    double H = 2.5 / sampleTime;
    double L = 5;
    double p = 0.5;

    // regulator:
    this->controller = new ControllerGPC(H, L, p, ident);
}

double SimulatorA::simulateController( double y ) {
    // filtr dolnoprzepustowy
    y = (y + last_y*alfa_y)/(1+alfa_y);
    last_y = y;

    // regulator GPC
    double u = controller->simulate( y );

    // filtr dolnoprzepustowy
    u = (u + last_u*alfa_u)/(1+alfa_u);
    last_u = u;

    return u;
}
