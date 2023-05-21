#include "clienttest.h"
#include "ui_clienttest.h"

ClientTest::ClientTest(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::ClientTest)
{
    _ui->setupUi(this);

    validationAdress();

    _socket = new QTcpSocket(this);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnect()));
    connect(_socket, SIGNAL(connected()), this, SLOT(socketIsConnected()));

    _isConnect = false;
}

ClientTest::~ClientTest()
{
    delete _ui;
}

void ClientTest::validationAdress()
{
    QString _adressRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp _adressRegex ("^" + _adressRange + "\\." + _adressRange + "\\." + _adressRange + "\\." + _adressRange + "$");
    //Применяю валидация с проверкой строки на соответсвие _adressRegex
    QRegExpValidator* _validAdress = new QRegExpValidator(_adressRegex, this);
    _ui->inputAdress->setValidator(_validAdress);
}

void ClientTest::on_ButtonConnectServer_clicked()
{
    int port = _ui->inputPort->text().toInt();
    QString adress = _ui->inputAdress->text();

    if (adress == "" ) _ui->ShowMessages->append("Необходимо ввести Адрес");
    else
    {
        if (port < 1000) _ui->ShowMessages->append("Необходимо ввести Порт (от 4-х символов)");
        else
        {
            if (_isConnect) _socket->disconnectFromHost();
            _ui->ShowMessages->clear();

            //Подключение к серверу по указанным пользователем данным
            _socket->connectToHost(adress, port);

            if (!_socket->waitForConnected(1000))
            {
                //Обработка ошибок подключения
                if (_socket->errorString() == "Connection refused")
                    _ui->ShowMessages->append("Невозможно подключиться к серверу");
                else if (_socket->errorString() == "Network unreachable")
                    _ui->ShowMessages->append("Сеть недоступна");
                else if (_socket->errorString() == "Socket operation timed out")
                    _ui->ShowMessages->append("Превышено время ожидания");
                else
                    _ui->ShowMessages->append(_socket->errorString());

                _isConnect = false;
            }
        }
    }
}

void ClientTest::socketIsConnected()
{
    sendToServer("Hello, server!");
    _isConnect = true;
    qDebug() << "send";
}

void ClientTest::socketReadyRead()
{
    QDataStream input(_socket);
    QString message;
    input >> message;
    _ui->ShowMessages->append(message);
}

void ClientTest::sendToServer(QString message)
{
    _data.clear();
    QDataStream send(&_data, QIODevice::WriteOnly);
    send << message;
    qDebug() << message;
    _socket->write(_data);
    _ui->inputMessage->clear();
}

void ClientTest::socketDisconnect()
{
    _socket->disconnectFromHost();
    _isConnect = false;
    _ui->ShowMessages->append("Сервер остановлен");
}

void ClientTest::on_sendMessage_clicked()
{
    if (_isConnect && _ui->inputMessage->text().length() >= 1)
    {
        _ui->ShowMessages->append(_ui->inputMessage->text());
        sendToServer(_ui->inputMessage->text());
    }
}

void ClientTest::on_inputMessage_returnPressed()
{
    if (_isConnect && _ui->inputMessage->text().length() >= 1)
    {
        _ui->ShowMessages->append(_ui->inputMessage->text());
        sendToServer(_ui->inputMessage->text());
    }
}

void ClientTest::on_sendImage_clicked()
{
    if (!_isConnect) return;

    if (_imageDirection == nullptr)
        _imageDirection = new QString();

    *_imageDirection = QFileDialog::getOpenFileName(this, "Выбор изображения", "", "PNG (*.png);; JPG (*.jpg)");

    if (*_imageDirection != "")
    {
        _image = new QImage(*_imageDirection);

        if (!_image->isNull())
        {
            sendImage();
        }
    }
}

void ClientTest::sendImage()
{
    _buffer = new QBuffer(this);
    _byteArray = new QByteArray();

    _imageWriter = new QImageWriter(_buffer, "PNG");
    _imageWriter->write(*_image);

    _data.clear();
    QDataStream send(_byteArray,QIODevice::WriteOnly);
    QString message = "";
    send << message <<(quint32)_buffer->data().size();

    _byteArray->append(_buffer->data());
    _socket->write(*_byteArray);
    _socket->waitForBytesWritten(3000);

    free(_byteArray);
    free(_imageWriter);

    return;
}
