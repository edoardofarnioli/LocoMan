#include <drc_shared/idynutils.h>
#include <yarp/sig/all.h>

namespace LocoMan {
    class CFLMM {
    iDynUtils _robot;
    public:
        CFLMM();
        ~CFLMM();

        bool update( const yarp::sig::Vector &q,
                     const yarp::sig::Vector &u,
                     const yarp::sig::Vector &f);

        yarp::sig::Matrix getPsi_q();
        yarp::sig::Matrix getPsi_tau();
        yarp::sig::Matrix getPsi_f();
        yarp::sig::Matrix getPsi_u();
        yarp::sig::Matrix getPsi_g();

        yarp::sig::Matrix getChi_q();
        yarp::sig::Matrix getChi_tau();
        yarp::sig::Matrix getChi_f();
        yarp::sig::Matrix getChi_u();
        yarp::sig::Matrix getChi_g();

        yarp::sig::Matrix getOmega_q();
        yarp::sig::Matrix getOmega_tau();
        yarp::sig::Matrix getOmega_f();
        yarp::sig::Matrix getOmega_u();
        yarp::sig::Matrix getOmega_g();
    };
}
