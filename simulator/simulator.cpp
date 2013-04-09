#include "simulator.h"

Simulator::Simulator()
{
    sp = std::vector<double>();
}

void Simulator::simulate() {
    std::fstream file;
    file.open(filePath.c_str(), std::ios::out|std::ios::trunc);

    double u = 0, y = 0, w = 0;

    // stan ustalony:
    for(int i = 0; i < spDuration*2; i++) {
        w = sp[0];
        setSP(w);
        u = simulateController( y );
        y = objective->simulate( u );
    }

    for (int j = 0; j < sp.size(); j++) {
        w = sp[j];
        setSP(w);
        for(int i = 0; i < spDuration; i++)
        {
            u = simulateController( y );
            y = objective->simulate( u );
            file << u << ";" << w << ";" << y << "\n";
        }
    }

    file.close();
}

void Simulator::setOutputFile(std::string n_filePath) {
    filePath = n_filePath;
}

void Simulator::setSP(double w) {
    controller->setSP(w);
}
