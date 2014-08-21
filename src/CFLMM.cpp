#include "LocoMan/CFLMM.h"

using namespace LocoMan;


CFLMM::CFLMM()
{

}

CFLMM::~CFLMM()
{

}

bool CFLMM::update(const yarp::sig::Vector &q,
                   const yarp::sig::Vector &u,
                   const yarp::sig::Vector &f,
                   const yarp::sig::Vector &Kq)
{
    return true;
}

yarp::sig::Matrix CFLMM::getPsi_q()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getPsi_tau()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getPsi_f()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getPsi_u()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getPsi_g()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getChi_q()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getChi_tau()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getChi_f()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getChi_u()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getChi_g()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getOmega_q()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getOmega_tau()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getOmega_f()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getOmega_u()
{
    return yarp::sig::Matrix();
}

yarp::sig::Matrix CFLMM::getOmega_g()
{
    return yarp::sig::Matrix();
}
