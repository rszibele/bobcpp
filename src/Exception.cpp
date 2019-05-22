#include <bobcpp/Exception.h>

namespace I2P {
namespace BOB  {
namespace Exception {

const char *BaseException::what() const noexcept {
    return message.c_str();
}

ConnectionTimeout::ConnectionTimeout() {
    message = "Connection to host timed out.";
}

ResponseUnexpected::ResponseUnexpected(const std::string &received, const std::string &expected)  {
    message = "Unexpected response \"" + received + "\". Expected: \"" + expected + "\"";
}

BobError::BobError(const std::string &bobMsg) {
    message = "BOB server returned ERROR.";
    if(!bobMsg.empty()) {
        message += " Information provided by the server: \"";
        message += bobMsg;
        message += "\".";
    }
}

SocketTimeout::SocketTimeout() {
    message = "The socket timed out during a blocking operation.";
}

WriteError::WriteError() {
    message = "Failed to write to the socket.";
}

ReadError::ReadError() {
    message = "Failed to write to the socket.";
}

}
}
}
