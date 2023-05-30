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

#include <shared_mutex>

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
    void SendMessage();

    bool _isMessage;
    std::shared_ptr<QBuffer> _buffer;
    std::shared_ptr<QByteArray> _byteArray;
    std::shared_ptr<QImage> _image;
    std::shared_ptr<QPixmap> _pixmap;
    std::shared_ptr<QImageWriter> _imageWriter;
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
