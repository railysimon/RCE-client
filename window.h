#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QUdpSocket>
#include <QFile>
#include <cstdlib>

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
        QUdpSocket *socket;
        QHostAddress rce_server;

private slots:
                void Send(QString message, QHostAddress address, int number);
                void Read();
                void StandartOutput();
};

#endif // WINDOW_H
