#include "arxidentification.h"


ARXIdentification::ARXIdentification()
{
    ARXIdentification(1, 0, 0.95);
}

ARXIdentification::ARXIdentification(int n_dB, int n_dA, double n_lambda):
    dB(n_dB),
    dA(n_dA),
    lambda(n_lambda)
{
    B = std::vector<double>(dB+1, 0);
    A = std::vector<double>(dA+1, 0);
    covarMatrix = boost::numeric::ublas::identity_matrix<double>(dA+dB+2)*1000;

    inQueue = std::deque<double>(dB+1, 0);
    outQueue = std::deque<double>(dA+1, 0);

    theta = boost::numeric::ublas::matrix<double>(dA+dB+2, 1);
    phi   = boost::numeric::ublas::matrix<double>(dA+dB+2, 1);

    fill(theta.begin1(), theta.end1(), 0);
    theta(0, 0) = 1;
    theta(dB+1, 0) = 1;

    temp1 = boost::numeric::ublas::matrix<double>(dA+dB+2, 1);
    temp3 = boost::numeric::ublas::matrix<double>(dA+dB+2, dA+dB+2);
    v_K = boost::numeric::ublas::matrix<double>(dA+dB+2, 1);
    n_B = std::vector<double> (dB+1, 1);
    n_A = std::vector<double> (dA+1, 1);
}

ModelData ARXIdentification::identify(double in, double out, double gamma)
{
    inQueue.push_front(in);
    outQueue.push_front(out);

    if ( inQueue.size() > dB + 1) inQueue.pop_back();
    if (outQueue.size() > dA + 1) outQueue.pop_back();

    std::copy( inQueue.begin(),  inQueue.end(), phi.begin1());       //S
    std::copy(outQueue.begin(), outQueue.end(), phi.begin1()+dB+1);  //R

    temp1 = prod(trans(phi), covarMatrix);
    temp1 = prod(temp1, phi);
    double temp2 = lambda + temp1(0,0);

    temp3 = prod(covarMatrix, phi);
    temp3 = prod(temp3, trans(phi));
    temp3 = prod(temp3, covarMatrix);

    covarMatrix = (covarMatrix - (temp3/temp2))/lambda;
    //std::cout << covarMatrix << "\n";

    v_K = prod(covarMatrix, phi);

    double epsilon = gamma - inner_product(theta.begin1(),theta.end1(),phi.begin1(),0.0);
    theta = theta + v_K*epsilon;

    std::copy(theta.begin1(), theta.begin1() + dB + 1, n_B.begin());
    std::copy(theta.begin1() + dB + 1, theta.end1(), n_A.begin());

    ModelData md = ModelData(n_B, n_A, 0);
    return md;
}

double ARXIdentification::getLambda(){
    return lambda;
}

void ARXIdentification::setLambda(double n_lambda){
    lambda = n_lambda;
}

void ARXIdentification::reset(){
    B = std::vector<double>(dB+1, 1);
    A = std::vector<double>(dA+1, 1);
    inQueue.clear();
    outQueue.clear();
    covarMatrix = boost::numeric::ublas::identity_matrix<double>(dA+dB+1)*1000;
    inQueue = std::deque<double>(inQueue.size(), 0);
    outQueue = std::deque<double>(outQueue.size(), 0);
    theta = boost::numeric::ublas::matrix<double>(dA+dB+1, 1);
    phi = boost::numeric::ublas::matrix<double>(dA+dB+1, 1);
    temp1 = boost::numeric::ublas::matrix<double>(dA+dB+1, 1);
    temp3 = boost::numeric::ublas::matrix<double>(dA+dB+1, dA+dB+1);
    v_K = boost::numeric::ublas::matrix<double>(dA+dB+1, 1);
    n_B = std::vector<double> (dB+1, 1);
    n_A = std::vector<double> (dA+1);
}
