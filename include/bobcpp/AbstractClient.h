#ifndef CLIENT_H
#define CLIENT_H

#include <bobcpp/Data.h>

namespace I2P {
namespace BOB {

template <typename TUInt16, typename TString, typename TListStatus>
class AbstractClient
{
public:
    virtual ~AbstractClient() {}

    virtual int getTimeout() = 0;
    virtual void setTimeout(const int timeout) = 0;
    
    virtual void connect(const TString &host = "localhost",
                         const TUInt16 port = 2827) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;

    virtual TString help() = 0;
    virtual void clear() = 0;
    virtual TString getdest() = 0;
    virtual TString getkeys() = 0;
    virtual TString getnick(const TString &tunnel) = 0;
    virtual void inhost(const TString &host) = 0;
    virtual void inport(const TString &port) = 0;
    virtual TListStatus list() = 0;
    virtual TString lookup(const TString &hostname) = 0;
    virtual TString newkeys() = 0;
    virtual void option(const TString &key, const TString &value) = 0;
    virtual void outhost(const TString &host) = 0;
    virtual void outport(const TString &port) = 0;
    virtual void quiet() = 0;
    virtual void quit() = 0;
    virtual TString setkeys(const TString &keys) = 0;
    virtual void setnick(const TString &nickname) = 0;
    virtual TString show() = 0;
    virtual TString showprops() = 0;
    virtual void start() = 0;
    virtual Data::Status status(const TString &nickname) = 0;
    virtual void stop() = 0;
    virtual void verify(const TString &key) = 0;
    virtual void visit() = 0;
    virtual void zap() = 0;

    virtual void sendLine(const TString &line) = 0;
    virtual TString readLine() = 0;
};

}
}

#endif // CLIENT_H
