#ifndef SERVERTEST_H
#define SERVERTEST_H

#include <QMainWindow>
#include "serverhandler.h"

namespace Ui {
class ServerTest;
}

class ServerTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerTest(QWidget* parent = 0);
    ~ServerTest();
    void closeEvent(QCloseEvent* event);


signals:
    void startServerSignal(int port);
    void sendMessageSignal(QString message, bool isClient);
    void closeProgramSignal();

private:
    Ui::ServerTest* _ui;
    ServerHandler* _server;
    QString* _port;
    void sendMessage();

public slots:
    void socketReadyRead(QString message);
    void sendToClient();

private slots:
    void on_ButtonStartServer_clicked();
    void on_sendMessage_clicked();
    void on_inputMessage_returnPressed();
};


#endif // SERVERTEST_H
