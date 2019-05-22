# **bobcpp** #

### A C++ I2P BOB client library

bobcpp is a C++ client library to communicate with the I2P BOB service.
It can be used to programatically manage tunnels to the I2P network.
After creating tunnels you can then connect to them on localhost with your application and communicate anonymously within the I2P network.

The BOB API documentation is available here: https://geti2p.net/en/docs/api/bob

At this moment there is only a Qt implementation (QTcpSocket) available, though by design it is easy to add another implementation (e.g. Boost ASIO, Winsock, etc.).

# Design

To keep the library as simple as possible it is implmented in a blocking fashion and throws exceptions when errors occur.
All methods will block and wait until the network actions are completed.
If you need to open/close tunnels without blocking then you can achieve this by using a worker thread.

# Quickstart Guide

The AbstractClient class provides the interface for the client.
It contains methods that correspond with the BOB commands, e.g. the method `client->inhost("localhost")` corresponds to the BOB command `inhost localhost`.

Below is an example of how to open a single tunnel.

```cpp
#include <bobcpp/bobcpp.h>
int main(int argc, char *argv[]) {
    try {
        auto client = CreateClient(); // returns implementation specific shared pointer
        client->connect(); // open a socket to the default BOB host and port

        client->setnick("my-tunnel");
        auto pubkey = client->newkeys();
        client->inhost("localhost");
        client->inport("33555");
        client->start();
        client->quit();

        client->disconnect(); // close the socket

        // Now you can connect your own TCP socket to localhost:33555
        // and send the destination on the first line (e.g. "zzz.i2p\n" without quotes)to connect to it.
        // After that you are directly communicating with the destination.
    } catch(...) {
        // see bobcpp/Exception.h for the possible exceptions you can handle / possibly recover from
    }
    return 0;
}
```

# Building

This project uses CMake to help build the project.

**Dependencies**

* CMake >= v3.1.0
* Qt5 Core, Network (currently the only available implementation)

**Build Instructions (Unix)**

```bash
git clone https://gitlab.com/rszibele/bobcpp.git
mkdir bobcpp-build
cd bobcpp-build
cmake ../bobcpp/
make
make install
```

# License

This project is licensed under the BSD 3-clause license, which can be found in the file LICENSE in the root of the project source code.
