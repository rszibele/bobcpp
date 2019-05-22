#ifndef BOBCPP_H
#define BOBCPP_H

#include <bobcpp/AbstractClient.h>

// TODO: FIXME
#define BOBCPP_QT 1

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
QSharedPointer<AbstractClient<quint16,
                               QString,
                               QList<Data::Status>>> CreateClient() {
    return QSharedPointer<QtClient>(new QtClient());
}
#endif
// Boost asio implementation
#ifdef BOBCPP_BOOST
shared_ptr<AbstractClient<uint16_t,
                          std::string,
                          std::vector<Data::Status>>> CreateClient() {
    return shared_ptr<BoostClient>(new BoostClient());
}
#endif
// BSD socket implementation
#ifdef BOBCPP_BSD
shared_ptr<AbstractClient<uint16_t,
                          std::string,
                          std::vector<Data::Status>>> CreateClient() {
    return shared_ptr<BsdClient>(new BsdClient());
#endif

}
}

#endif // BOBCPP_H
