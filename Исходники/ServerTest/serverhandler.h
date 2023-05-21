#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QDateTime>
#include <QCloseEvent>

#include "imageform.h"
#include <QByteArray>
#include <QLabel>
#include <QImageReader>
#include <QBuffer>


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

    QFile _file;
    ImageForm* _imageForm;
    quint32 _packetSize;
    QDataStream *_stream;
    QByteArray *_arrayOfData;
    void showImage();

signals:
    void socketReadyReadSignal(QString message);
    void sendMessageSignal();
    QString showMessage(QString message);
    void invokeImageFrame(QImage _image);

public slots:
    void startServer(int port);
    void incomingConnection(qintptr socketID);
    void socketReadyRead();
    void socketDisconnect();
    void sendMessage(QString message, bool isClient);
    void sendMessage(QString message);
    void closeProgram();
};

#endif // SERVERHANDLER_H
