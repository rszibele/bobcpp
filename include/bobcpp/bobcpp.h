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

// Qt implementation
#ifdef BOBCPP_QT
using BobClient = AbstractClient<quint16, QString, QList<Data::Status>>;
QSharedPointer<BobClient> CreateClient() {
    return QSharedPointer<QtClient>(new QtClient());
}
#endif
// Boost asio implementation
#ifdef BOBCPP_BOOST
//using BobClient =;
shared_ptr<BobClient> CreateClient() {
    return shared_ptr<BoostClient>(new BoostClient());
}
#endif
// BSD socket implementation
#ifdef BOBCPP_BSD
//using BobClient = ;
shared_ptr<BobClient> CreateClient() {
    return shared_ptr<BsdClient>(new BsdClient());
#endif

}
}

#endif // BOBCPP_H
