#ifndef BOBCPP_DATA_H
#define BOBCPP_DATA_H

#define BOBCPP_QT 1
#ifdef BOBCPP_QT
    #include <QString>
#endif

namespace I2P {
namespace BOB {
namespace Data {

template <typename TUint16, typename TString>
class StatusBase {
public:
    TString nickname;
    bool starting;
    bool running;
    bool stopping;
    bool keys;
    bool quiet;
    uint16_t inport;
    TString inhost;
    uint16_t outport;
    TString outhost;
};

#ifdef BOBCPP_QT
    typedef StatusBase<quint16, QString> Status;
#endif

}
}
}

#endif // DATATYPES_H
