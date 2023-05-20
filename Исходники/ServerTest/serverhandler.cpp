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
    _sockets.prepend(_socket);
    qDebug() << "Сокет" << socketID << "добавлен в контейнер";

    sendClientLog("Клиент подключился");
    sendToThisClient("Hello, client!");
}

void ServerHandler::socketReadyRead()
{
    _socket = (QTcpSocket*)sender();

    QDataStream input(_socket);
    QString message;
    input >> message;

    sendClientLog(message);
    emit socketReadyReadSignal(message);
}

void ServerHandler::sendToClient(QString message, bool isClient)
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

void ServerHandler::sendToThisClient(QString message)
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
    sendClientLog("Клиент отключился");

    //Удаляю из контейнера отключившийся сокет
    for (int i = 0; i < _sockets.size(); i++)
        if (_sockets[i] == _socket) _sockets.removeAt(i);

    _socket -> deleteLater();
}

//Отправляю лог от имени сервера
void ServerHandler::sendServerLog(QString text)
{
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QString currentAdress = _serverAdress + ":" + QString::number(_serverPort);
    QString currentLog = dateTime + " | " + currentAdress +  " | " + text;
    qDebug() << currentLog;
    writeLogFile(currentLog);
}

//Отправляю лог от имени клиента
void ServerHandler::sendClientLog(QString text)
{
    QString dateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    QString currentLog = dateTime + " | " + adressFormated() +  " | " + text;
    qDebug() << currentLog;
    writeLogFile(currentLog);
}

//Получаю нужнйы формат адреса клиента
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
    file.setFileName("log.txt");

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Неудается обратиться к файлу";
        return;
    } qDebug() << "Файл открыт";
}

void ServerHandler::writeLogFile(QString text)
{
    QTextStream writeFile(&file);
    writeFile << text << "\n";
}

void ServerHandler::closeProgram()
{
    sendServerLog("Сервер остановлен");
    qDebug() << "Сервер остановлен";
    file.flush();
    file.close();
}
