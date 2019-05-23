#ifndef BOBCPP_H
#define BOBCPP_H

#include <bobcpp/AbstractClient.h>

// implementation specific includes
#ifdef BOBCPP_QT
    #include <QSharedPointer>
    #include <bobcpp/QtClient.h>
#endif
#ifdef BOBCPP_BOOST
#endif
#ifdef BOBCPP_BSD
#endif

namespace I2P {
namespace BOB {

// Qt
#ifdef BOBCPP_QT
    using BobClient = AbstractClient<quint16, QString, QList<Data::Status>>;
#endif
// Boost asio
#ifdef BOBCPP_BOOST
#endif
// BSD socket
#ifdef BOBCPP_BSD
#endif

QSharedPointer<BobClient> CreateClient();

}
}

#endif // BOBCPP_H
