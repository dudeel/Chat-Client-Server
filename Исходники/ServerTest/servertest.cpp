#include "servertest.h"
#include "ui_servertest.h"

ServerTest::ServerTest(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::ServerTest)
{
    _ui->setupUi(this);

    _server = new ServerHandler();
    connect(this, &ServerTest::startServerSignal, _server, &ServerHandler::startServer);
    connect(this, &ServerTest::sendMessageSignal, _server, &ServerHandler::sendToClient);
    connect(this, &ServerTest::closeProgramSignal, _server, &ServerHandler::closeProgram);

    connect(_server, &ServerHandler::socketReadyReadSignal, this, &ServerTest::socketReadyRead);
    connect(_server, &ServerHandler::sendMessageSignal, this, &ServerTest::sendToClient);
    connect(_server, &ServerHandler::showMessage, this, &ServerTest::socketReadyRead);
}

ServerTest::~ServerTest()
{
    delete _ui;
}

void ServerTest::socketReadyRead(QString message)
{
    _ui->ShowMessages->append(message);
}

void ServerTest::sendToClient()
{
    _ui->inputMessage->clear();
}

void ServerTest::on_ButtonStartServer_clicked()
{
    int port = _ui->inputPort->text().toInt();

    //Добавил валидацию, скрипт принимает порт размером от 4-х символов
    if (port > 1000) emit startServerSignal(port);
    else qDebug() << "Write port!";
}

void ServerTest::on_sendMessage_clicked()
{
    sendMessage();
}

void ServerTest::on_inputMessage_returnPressed()
{
    sendMessage();

}

void ServerTest::sendMessage()
{
    if (_ui->inputMessage->text().length() >= 1)
    {
        socketReadyRead(_ui->inputMessage->text());
        emit sendMessageSignal(_ui->inputMessage->text(), false);
        _ui->inputMessage->clear();
    }
}

void ServerTest::closeEvent(QCloseEvent* event)
{
    event->ignore();
    emit closeProgramSignal();
    event->accept();
}
