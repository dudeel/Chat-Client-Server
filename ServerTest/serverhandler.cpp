#include "serverhandler.h"

//Запуск сервера и ожидание клиентов
void ServerHandler::startServer(int port)
{
    openLogFile();

    if (this->listen(QHostAddress::Any, port))
    {
        //Для прототипа локальное подключение
        _serverAdress = "127.0.0.1";
        _serverPort = port;
        emit socketReadyReadSignal("Сервер запущен");
        sendServerLog("Сервер запущен");
    }
    else
        sendServerLog("Не удалось запустить сервер");
}

//Ловим подключение клиента к серверу
void ServerHandler::incomingConnection(qintptr socketID)
{
    _socket = new QTcpSocket(this);
    //Присваиваю уникальный номер сокету
    _socket->setSocketDescriptor(socketID);
    qDebug() << "Номер сокета:" << socketID;

    connect(_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnect()));

    //Контейнер сокетов
    _sockets.push_back(_socket);
    qDebug() << "Сокет" << socketID << "добавлен в контейнер";

    sendClientLog("Клиент подключился");
    sendMessage("Hello, client!");
}

void ServerHandler::socketReadyRead()
{
    _socket = (QTcpSocket*)sender();
    QString message;

    if(_packetSize == 0)
    {
        _stream = std::shared_ptr<QDataStream>(new QDataStream(_socket));
        if((quint64)_socket->bytesAvailable() < sizeof(quint32))
            return;

        *_stream >> message >> _packetSize;
    }

    if(_packetSize > _socket->bytesAvailable())
        return;

    _arrayOfData = new QByteArray();
    *_arrayOfData = _socket->read(_packetSize);

    if (message == "") showImage();
    else
    {
        sendClientLog(message);
        emit socketReadyReadSignal(message);
    }

    _packetSize = 0;
}

void ServerHandler::showImage()
{
    qDebug() << "_packetSize = " << _packetSize;

    QImage _image;
    QBuffer buffer(_arrayOfData);
    buffer.open(QIODevice::ReadOnly);
    QImageReader _imageReader(&buffer, "PNG");
    _image = _imageReader.read();

    _imageForm = new ImageForm();
    _imageForm->openImageFrame(_image);
    _imageForm->show();

    sendClientLog("Отправил изображение");
}

void ServerHandler::sendMessage(QString message, bool isClient)
{
    _data.clear();
    QDataStream send(&_data, QIODevice::WriteOnly);
    send << message;

    //Для логов
    if (isClient) sendClientLog(message);
    else sendServerLog(message);

    //Отправка сообщения всем сокетам из контейнера
    for (int i = 0; i < _sockets.size(); i++)
        _sockets[i]->write(_data);
}

void ServerHandler::sendMessage(QString message)
{
    _data.clear();
    QDataStream send(&_data, QIODevice::WriteOnly);
    send << message;

    sendServerLog(message);
    _socket->write(_data);
}

//Обработка отключение клиента
void ServerHandler::socketDisconnect()
{
    _socket = (QTcpSocket*)sender();
    sendClientLog("Клиент отключился");
    _sockets.removeAll(_socket);
    for (int i = 0; i < _sockets.size(); i++)
        qDebug() << _sockets[i]->peerAddress() << _sockets[i]->peerPort();
}

//Отправляю лог от имени сервера
void ServerHandler::sendServerLog(QString text)
{
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QString currentAdress = _serverAdress + ":" + QString::number(_serverPort);
    QString currentLog = dateTime + "\t| " + currentAdress +  "\t| " + text;
    qDebug() << currentLog;
    writeLogFile(currentLog);
}

//Отправляю лог от имени клиента
void ServerHandler::sendClientLog(QString text)
{
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QString currentLog = dateTime + "\t| " + adressFormated() +  "\t| " + text;
    qDebug() << currentLog;
    writeLogFile(currentLog);
}

//Получаю нужный формат адреса клиента
QString ServerHandler::adressFormated()
{
    QString adress = _socket->peerAddress().toString();
    QString port = QString::number(_socket->peerPort());

    //Функция возвращает помимо адреса дополнительную инфу, убираю её из вывода
    QString currentAdress = adress.remove(0,7) + ":" + port;

    return currentAdress;
}

void ServerHandler::openLogFile()
{
    _file.setFileName("log.txt");

    if (!_file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Неудается обратиться к файлу";
        return;
    } qDebug() << "Файл открыт";
}

void ServerHandler::writeLogFile(QString text)
{
    QTextStream writeFile(&_file);
    writeFile << text << "\n";
}

void ServerHandler::closeProgram()
{
    sendServerLog("Сервер остановлен");
    qDebug() << "Сервер остановлен";
    _file.flush();
    _file.close();
}

