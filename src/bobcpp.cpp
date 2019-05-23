#include <bobcpp/bobcpp.h>

namespace I2P {
namespace BOB {

QSharedPointer<BobClient> CreateClient() {
// Qt
#ifdef BOBCPP_QT
    return QSharedPointer<QtClient>(new QtClient());
#endif
// Boost asio
#ifdef BOBCPP_BOOST
#endif
// BSD socket
#ifdef BOBCPP_BSD
#endif
}

}
}
