#ifndef BOBCPP_EXCEPTION_H
#define BOBCPP_EXCEPTION_H

#include <exception>

#include <QString>
#include <QStringBuilder>

namespace I2P {
namespace BOB  {
namespace Exception {

class BaseException : public std::exception {
public:
    const char *what() const noexcept override;
protected:
    std::string message;
};

class ConnectionTimeout : public BaseException {
public:
    ConnectionTimeout();
};

class ResponseUnexpected : public BaseException {
public:
    ResponseUnexpected(const std::string &received, const std::string &expected);
};

class BobError : public BaseException {
public:
    BobError(const std::string &bobMsg);
};

class SocketTimeout : public BaseException {
public:
    SocketTimeout();
};

class WriteError : public BaseException {
public:
    WriteError();
};

class ReadError : public BaseException {
public:
    ReadError();
};

}
}
}

#endif // EXCEPTIONS_H
