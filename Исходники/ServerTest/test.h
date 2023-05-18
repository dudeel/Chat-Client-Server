#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class QTcpServer;

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

private:
    QTcpSocket* socket;
    QByteArray Data;

public slots:
    void startServer();
    void incomingConnection(qintptr socketID) ;
    void socketReady();
    void socketDisconnect();
};

#endif // TEST_H
