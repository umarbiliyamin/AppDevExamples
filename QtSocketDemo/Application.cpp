#include "Application.h"
#include <QDataStream>

Application::Application(int argc, char *argv[], SocketServer &server, SocketClient &client)
    : QCoreApplication(argc,argv), server(server), client(client), counter(0)
{
    connect(&client, &SocketClient::dataReady, this, &Application::clientDataReady);
    connect(&server, &SocketServer::dataReady, this, &Application::serverDataReady);
    connect(&timer, &QTimer::timeout, this, &Application::tick);
}

void Application::clientDataReady(QDataStream& inStream)
{
    QString text;
    inStream >> text;
    qWarning() << "Message received on the client socket: " << text;
}

void Application::serverDataReady(QDataStream& inStream)
{
    QString text;
    inStream >> text;
    qWarning() << "Message received on the server socket: " << text;

    if (text == "What's up, Doc?")
    {
        server.send("Everything OK.");
    }
}

void Application::startSending()
{
    timer.start(1000);
}

void Application::tick()
{
    qDebug() << "Application::tick called";
    counter++;
    if (counter > 10)
    {
        qDebug() << "The tick executed 10 times, demo is ending.";
        // The QCoreApplication class has exit() method.
        this->exit(0);
        return;
    }
    client.send(QString("What's up, Doc?"));
}
