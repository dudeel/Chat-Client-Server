#ifndef CLIENTTEST_H
#define CLIENTTEST_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDataStream>

namespace Ui {
class ClientTest;
}

class ClientTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientTest(QWidget *parent = 0);
    ~ClientTest();

private:
    Ui::ClientTest* _ui;
    QTcpSocket* _socket;
    QByteArray _data;
    bool _isConnect;

    void validationAdress();
    void sendToServer(QString message);

public slots:
    void socketReadyRead();
    void socketDisconnect();
    void socketIsConnected();

private slots:
    void on_ButtonConnectServer_clicked();
    void on_sendMessage_clicked();
    void on_inputMessage_returnPressed();
};

#endif // CLIENTTEST_H
