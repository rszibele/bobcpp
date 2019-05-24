#include <bobcpp/QtClient.h>

#include <bobcpp/Exception.h>

#include <QStringBuilder>
#include <QRegularExpression>

namespace I2P {
namespace BOB {

QtClient::QtClient() {
    timeout = 1000 * 60 * 5; // 5 minutes
}

QtClient::~QtClient() {
    if(isConnected()) {
        disconnect();
    }
}

int QtClient::getTimeout() {
    return timeout;
}
void QtClient::setTimeout(const int timeout) {
    this->timeout = timeout;
}

void QtClient::connect(const QString &host,
                     const quint16 port) {
    socket.connectToHost(host, port);
    if(!socket.waitForConnected(timeout)) {
        throw Exception::ConnectionTimeout();
    }

    // first line should be "BOB {VERSION}"
    if(readLine() != "BOB 0.0.10") {
        // TOOD: warning
    }

    // second line should be "OK"
    const QString r = readLine();
    if(!r.startsWith("OK")) {
        throw Exception::ResponseUnexpected(r.toStdString(), "OK");
    }
}
void QtClient::disconnect() {
    socket.disconnectFromHost();
}
bool QtClient::isConnected() {
    return socket.state() == QTcpSocket::ConnectedState;
}

QString QtClient::help() {
    return execStringRet("help");
}
void QtClient::clear() {
    exec("clear");
}
QString QtClient::getdest() {
    return execStringRet("getdest");
}
QString QtClient::getkeys() {
    return execStringRet("getkeys");
}
QString QtClient::getnick(const QString &tunnel) {
    return execStringRet("getnick", tunnel);
}
void QtClient::inhost(const QString &host) {
    exec("inhost", host);
}
void QtClient::inport(const QString &port) {
    exec("inport", port);
}
QList<Data::Status> QtClient::list() {
    return execStatusList("list");
}
QString QtClient::lookup(const QString &hostname) {
    return execStringRet("lookup", hostname);
}
QString QtClient::newkeys() {
    return execStringRet("newkeys");
}
void QtClient::option(const QString &key, const QString &value) {
    exec("option", key % "=" % value);
}
void QtClient::outhost(const QString &host) {
    exec("outhost", host);
}
void QtClient::outport(const QString &port) {
    exec("outport", port);
}
void QtClient::quiet(const bool quiet) {
    exec("quiet", quiet ? "True" : "False");
}
void QtClient::quit() {
    exec("quit");
}
QString QtClient::setkeys(const QString &keys) {
    return execStringRet("setkeys", keys);
}
void QtClient::setnick(const QString &nick) {
    exec("setnick", nick);
}
QString QtClient::show() {
    return execStringRet("show");
}
QString QtClient::showprops() {
    return execStringRet("showprops");
}
void QtClient::start() {
    exec("start");
}
Data::Status QtClient::status(const QString &tunnel) {
    return execStatusRet("status", tunnel);
}
void QtClient::stop() {
    exec("stop");
}
void QtClient::verify(const QString &key) {
    exec("verify", key);
}
void QtClient::visit() {
    exec("visit");
}
void QtClient::zap() {
    exec("zap");
}

void QtClient::sendLine(const QString &line) {
    QByteArray ba = (line % "\n").toUtf8();
    qint64 r = socket.write(ba);
    if(!socket.waitForBytesWritten(timeout)) {
        throw Exception::SocketTimeout();
    }
    if(ba.length() != r) {
        throw Exception::WriteError();
    }
}
QString QtClient::readLine() {
    while(!socket.canReadLine()) {
        if(!socket.waitForReadyRead(timeout)
                && socket.bytesAvailable() < 1) { // required for windows, as it may time out even when receiving
            throw Exception::SocketTimeout();
        }
    }
    QString result = QString(socket.readLine());
    // remove newline character
    if(!result.isEmpty()) {
        result.chop(1);
    }
    return result;
}

void QtClient::exec(const QString &cmd, const QString &arg) {
    QString data = cmd;
    if(!arg.isEmpty()) {
        data += " " % arg;
    }
    sendLine(data);
    QString line = readLine();
    if(isError(line)) {
        throw Exception::BobError(removeError(line).toStdString());
    }
}
QString QtClient::execStringRet(const QString &cmd, const QString &arg) {
    QString data = cmd;
    if(!arg.isEmpty()) {
        data += " " % arg;
    }
    sendLine(data);
    QString line = readLine();
    if(isError(line)) {
        throw Exception::BobError(removeError(line).toStdString());
    }
    return removeOk(line);
}
Data::Status QtClient::execStatusRet(const QString &cmd, const QString &tunnel) {
    sendLine(cmd % " " % tunnel);
    QString line = readLine();
    if(isError(line)) {
        throw Exception::BobError(removeError(line).toStdString());
    }

    Data::Status result;
    if(!parseStatus(removeData(line), &result)) {
        throw std::runtime_error(QString("Failed to parse status line: \"" % line % "\"").toStdString());
    }

    return result;
}
QList<Data::Status> QtClient::execStatusList(const QString &cmd) {
    sendLine(cmd);
    QString line = readLine();
    if(isError(line)) {
        throw Exception::BobError(removeError(line).toStdString());
    }

    QList<Data::Status> result;
    Data::Status status;
    while(!line.startsWith("OK")) {
        parseStatus(removeData(line), &status);
        result.append(status);
        line = readLine();
    }

    return result;
}

bool QtClient::isError(const QString &line) {
    return line.startsWith("ERROR");
}
QString QtClient::removeOk(const QString &line) {
    return line.startsWith("OK") ? line.mid(3) : line;
}
QString QtClient::removeError(const QString &line) {
    return line.startsWith("ERROR") ? line.mid(6) : line;
}
QString QtClient::removeData(const QString &line) {
    return line.startsWith("DATA") ? line.mid(5) : line;
}

QMap<QString, QString> QtClient::parseKeyValues(const QString &line) {
    QMap<QString, QString> map;
    QRegularExpression regex("([^\\s]+):\\s([^\\s]+)"); // matches: "KEY: value"
    QRegularExpressionMatchIterator i = regex.globalMatch(line);

    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if(match.hasMatch()) {
            const QString key = match.captured(1);
            const QString value = match.captured(2);
            map[key] = value;
        }
    }

    return map;
}

bool QtClient::parseStatus(const QString &line, Data::Status *status) {
    Q_ASSERT(status != nullptr);

    QMap<QString, QString> map = parseKeyValues(line);
    if(map.size() == 0) {
        return false;
    }

    // set status
    status->nickname = map.contains("NICKNAME") ? map["NICKNAME"] : "";
    status->starting = map.contains("STARTING") ? map["STARTING"] == "true" : false;
    status->running = map.contains("RUNNING") ? map["RUNNING"] == "true" : false;
    status->stopping = map.contains("STOPPING") ? map["STOPPING"] == "true" : false;
    status->keys = map.contains("KEYS") ? map["KEYS"] == "true" : false;
    status->quiet = map.contains("QUIET") ? map["QUIET"] == "true" : false;
    status->inport = map.contains("INPORT") ? map["INPORT"].toUShort() : 0;
    status->inhost = map.contains("INHOST") ? map["INHOST"] : "";
    status->outport = map.contains("OUTPORT") ? map["OUTPORT"].toUShort() : 0;
    status->outhost = map.contains("OUTHOST") ? map["OUTHOST"] : "";

    return true;
}

}
}
