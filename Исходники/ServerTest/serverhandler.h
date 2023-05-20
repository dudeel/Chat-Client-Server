#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

#include <QFile>
#include <QDateTime>
#include <QCloseEvent>


class ServerHandler : public QTcpServer
{
    Q_OBJECT

private:
    QTcpSocket* _socket;
    QList <QTcpSocket*> _sockets;
    QByteArray _data;
    QString _serverAdress;
    int _serverPort;
    QString adressFormated();
    void sendServerLog(QString text);
    void sendClientLog(QString text);
    void openLogFile();
    void writeLogFile(QString text);
    QFile file;

signals:
    void socketReadyReadSignal(QString message);
    void sendMessageSignal();
    QString showMessage(QString message);

public slots:
    void startServer(int port);
    void incomingConnection(qintptr socketID);
    void socketReadyRead();
    void socketDisconnect();
    void sendToClient(QString message, bool isClient);
    void sendToThisClient(QString message);
    void closeProgram();
};

#endif // SERVERHANDLER_H
