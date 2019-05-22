#ifndef QTCLIENT_H
#define QTCLIENT_H

#include <bobcpp/AbstractClient.h>
#include <bobcpp/Data.h>

#include <QString>
#include <QList>
#include <QMap>
#include <QTcpSocket>

namespace I2P {
namespace BOB {

class QtClient : public AbstractClient< quint16,
                                        QString,
                                        QList<Data::Status> >
{
public:
    QtClient();
    ~QtClient() override;

    void connect(const QString &host = "localhost",
                 const uint16_t port = 2827,
                 const int timeout = 5 * 1000) override;
    void disconnect() override;
    bool isConnected() override;

    QString help() override;
    void clear() override;
    QString getdest() override;
    QString getkeys() override;
    QString getnick(const QString &tunnel) override;
    void inhost(const QString &host) override;
    void inport(const QString &port) override;
    QList<Data::Status> list() override;
    QString lookup(const QString &hostname) override;
    QString newkeys() override;
    void option(const QString &key, const QString &value) override;
    void outhost(const QString &host) override;
    void outport(const QString &port) override;
    void quiet() override;
    void quit() override;
    QString setkeys(const QString &keys) override;
    void setnick(const QString &nickname) override;
    QString show() override;
    QString showprops() override;
    void start() override;
    Data::Status status(const QString &nickname) override;
    void stop() override;
    void verify(const QString &key) override;
    void visit() override;
    void zap() override;

    void sendLine(const QString &line) override;
    QString readLine() override;

protected:
    void exec(const QString &cmd, const QString &arg = QString());
    QString execStringRet(const QString &cmd, const QString &arg = QString());
    Data::Status execStatusRet(const QString &cmd, const QString &tunnel);
    QList<Data::Status> execStatusList(const QString &cmd);

    bool isError(const QString &line);
    QString removeOk(const QString &line);
    QString removeError(const QString &line);
    QString removeData(const QString &line);
    QMap<QString, QString> parseKeyValues(const QString &line);
    bool parseStatus(const QString &line, Data::Status *status);

    QTcpSocket socket;
};

}
}

#endif // QTCLIENT_H
