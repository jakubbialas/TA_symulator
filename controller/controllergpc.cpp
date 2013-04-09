#include "controllergpc.h"\

ControllerGPC::ControllerGPC() :
    ControllerGPC(1, 1, 0, new ModelIdentification())
{
}

ControllerGPC::ControllerGPC(double n_H, double n_L, double n_p, ModelIdentification * n_ident) :
    H(n_H),
    L(n_L),
    p(n_p)
{
    ident = n_ident;
    Y = std::deque<double>(20, 0);
    U = std::deque<double>(20, 0);
    W = std::deque<double>(20, 0);
}

void ControllerGPC::setParameters(double n_H, double n_L, double n_p, ModelIdentification * n_ident){
    H = n_H;
    L = n_L;
    p = n_p;
    ident = n_ident;
}

double ControllerGPC::simulate(double y){
    double w = sp;

    W.push_front(w);
    Y.push_front(y);

    // identyfikacja modelu i stworzenie modelu:
    ModelData md = ident->identify(W[0], U[0], Y[0]);

    DiscreteObject obj1(md);

    // symulacja odpowiedzi swobodnej:
    boost::numeric::ublas::matrix<double> h(H,1);
    for(int i=0; i<H; i++){
        h(i,0) = obj1.simulate(1);
    }

    // wypełnienie macierzy Q:
    boost::numeric::ublas::matrix<double> Q(H,L);
    for(int i=0; i<H; i++){
        for(int j=0; j<L; j++){
            if(i-j<0){
                Q(i,j) = 0;
            }else{
                Q(i,j) = h(i-j,0);
            }
        }
    }

    boost::numeric::ublas::matrix<double> otemp(L,L);
    boost::numeric::ublas::matrix<double> otemp2(L,L);

    otemp = prod(trans(Q), Q);
    otemp = otemp + boost::numeric::ublas::identity_matrix<double>(L)*p;

    double u;

    try{
        otemp2.assign(boost::numeric::ublas::identity_matrix<double>(L));
        boost::numeric::ublas::permutation_matrix<> pm(L);
        lu_factorize(otemp,pm);
        lu_substitute(otemp,pm,otemp2);


        boost::numeric::ublas::matrix<double> q(1,H);
        boost::numeric::ublas::matrix<double> otemp3(1,L,0);
        otemp3(0,0) = 1;

        boost::numeric::ublas::matrix<double> otemp4(L,1);

        otemp4 = prod(otemp3, otemp2);
        q = prod(otemp4, trans(Q));

        //std::cout << "q " << q << std::endl;

        boost::numeric::ublas::matrix<double> W0(H,1);
        boost::numeric::ublas::matrix<double> Y0(H,1);

        DiscreteObject obj2(md);
        obj2.setU(U);
        obj2.setY(Y);

        for(int i=0; i<H; i++){
            W0(i,0) = w; //this->source->getSample(i+1);
            Y0(i,0) = obj2.simulate(U[0]);
        }
        boost::numeric::ublas::matrix<double> temp4(1,1);
        temp4 = prod(q, W0-Y0);

        u = U[0] + temp4(0,0);

    }catch(...){
        u = w;
    }

    if (u>0.8627) u = 0.8627;
    if (u<0) u = 0;

    U.push_front(u);


    // pop unused values:
    U.pop_back();
    Y.pop_back();
    W.pop_back();

    return u;
}

void ControllerGPC::reset(){
    W.clear();
    Y.clear();
    U.clear();
    W = std::deque<double>(20, 0);
    Y = std::deque<double>(20, 0);
    U = std::deque<double>(20, 0);
    Controller::reset();
}
