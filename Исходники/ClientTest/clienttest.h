#ifndef CLIENTTEST_H
#define CLIENTTEST_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDataStream>

#include <QFileDialog>
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QImageWriter>

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

    bool _isMessage;
    QString* _imageDirection;
    QBuffer* _buffer;
    QByteArray* _byteArray;
    QImage* _image;
    QPixmap* _pixmap;
    QImageWriter* _imageWriter;
    void sendImage();

public slots:
    void socketReadyRead();
    void socketDisconnect();
    void socketIsConnected();

private slots:
    void on_ButtonConnectServer_clicked();
    void on_sendMessage_clicked();
    void on_inputMessage_returnPressed();
    void on_sendImage_clicked();
};

#endif // CLIENTTEST_H
