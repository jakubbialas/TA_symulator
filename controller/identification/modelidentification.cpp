#include "modelidentification.h"

ModelIdentification::ModelIdentification()
{
    temp = 0;
    temp_w = 0;
}

void ModelIdentification::setSampleTime(double n_sampleTime) {
    sampleTime = n_sampleTime;
}

ModelData ModelIdentification::identify(double w, double u, double y){
    // stałe pierwszego zbiornika:
    double A1 = 0.7329;
    double H1 = 4.6526;
    double kv1 = 0.2113;

    // stałe drugiego zbiornika:
    double tgalfa2 = 4.2687;
    double kv2 = 0.4336;

    // punkt pracy:
    // pierwszego zbiornika:

    // 1. punktu pracy pierwszego zbiornika nie można dokłądnie określić.
    // poprawne wyznaczenie punktu pracy jest szczegulnie ważne w chwili przelania.
    // orientacyjnie przyjmujemy punkt pracy do którego dążymy.
    //double h1 = pow(2, w/kv1);
    // 2. drobna symulacja ktora jest niżej
    // można sobie na nią pozwolić ponieważ w stanie ustalonym wszystkie błędy i tak znikną
    double h1 = temp;
    // 3. próba średniej ważonej obu pomysłów:
    //double w1 = 100;
    //double w2 = sampleTime; // waga zależna od czasu próbkowania:
    //double h1 = (temp * w1 + pow(2, w/kv1) * w2) / (w1 + w2);

    // drugiego zbiornika:
        // punkt pracy drugiego zbiornika to dokładnie jego wypływ.
    double q20 = y;

    //parametry pierwszego zbiornika:
    double b10;
    double a11;
    double op1;

    // obliczenie wypływu z pierwszego zbiornika na podstawie punktu pracy:
    double q10 = sqrt(h1) * kv1;

    // sprawdzenie czy zbiornika jest pełny:
    bool fullTank = ( h1 >= H1 );

    if (!fullTank) {
        // dla niepelnego zbiornika:

        // transmitancja ciagla pierwszego zbiornika:
        // K(s) = k / (1 + sT)
        double T1 = A1 * 2 * q10 / (kv1 * kv1);
        double k1 = 1;

        // transmitancja dyskretna pierwszego zbiornika:
        // H(z^-1) = b0 / (1 + a1*(z^-1)
        a11 = - pow(M_E, - (sampleTime / T1));
        b10 = k1 * (1 + a11);
        op1 = 1;
    } else {
        // dla pelnego zbiornika:

        // transmitancja ciagla pierwszego zbiornika:
        // K(s) = k / (1 + sT)
        // k1 = 1;
        // T1 = 0;
        // K(s) = 1;

        // transmitancja dyskretna pierwszego zbiornika:
        // H(z^-1) = b0 / (1 + a1*(z^-1))
        a11 = 0;
        b10 = 1;
        op1 = 0;
        // H(z^-1) = 1;
    }

    // aktualizacja punktu pracy:
    h1 = h1 + (u - q10)/A1 * sampleTime;
    // sprawdzenie przepełnienia i pustego:
    h1 = h1 < 0 ? 0 : (h1 > H1 ? H1 : h1);
    // aktualizacja zmiennej prywatnej:
    temp = h1;

    // transmitancja ciagla drugiego zbiornika w punkcie pracy:
    // K(s) = k / (1 + sT)
    double T2 = ( 2 * M_PI * pow(q20,5) ) / ( tgalfa2 * tgalfa2 * pow(kv2,6) );
    double k2 = 1;

    // transmitancja dyskretna drugiego zbiornika w punkcie pracy:
    // H(z^-1) = b0 / (1 + a1*(z^-1))
    double a21 = - pow(M_E, - (sampleTime / T2));
    double b20 = k2 * (1 + a21);
    double op2 = 1;

    // transmitancja końcowa:
    double b0 = b10 * b20;
    double a0 = 1;
    double a1 = a11 + a21;
    double a2 = a11 * a21;
    double op = op1 + op2;

    std::vector<double> B;
    std::vector<double> A;

    B.push_back(b0);
    A.push_back(a0);
    A.push_back(a1);
    A.push_back(a2);

    //std::cout << ModelData(B, A, op) << "\n";

    return ModelData(B, A, op);
    // mamy model drugiego rzędu z opóźnieniem równym 2
    // lub model pierwszego rzędu z opóźnieniem równym 1
    // więc w sumie to jest to niestacjonarność...
}
