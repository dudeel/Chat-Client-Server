#include "servertest.h"
#include "ui_servertest.h"

ServerTest::ServerTest(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::ServerTest)
{
    _ui->setupUi(this);

    _server = new ServerHandler();
    connect(this, SIGNAL(startServerSignal(int)), _server, SLOT(startServer(int)));
    connect(this, SIGNAL(sendMessageSignal(QString,bool)), _server, SLOT(sendMessage(QString,bool)));
    connect(this, SIGNAL(closeProgramSignal()), _server, SLOT(closeProgram()));

    connect(_server, SIGNAL(socketReadyReadSignal(QString)), this, SLOT(socketReadyRead(QString)));
    connect(_server, SIGNAL(sendMessageSignal()), this, SLOT(sendToClient()));
    connect(_server, SIGNAL(showMessage(QString)), this, SLOT(socketReadyRead(QString)));
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

    //Cкрипт принимает порт размером от 4-х символов
    if (port < 1000) _ui->ShowMessages->append("Необходимо ввести Порт (от 4-х символов)");
    else emit startServerSignal(port);
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
