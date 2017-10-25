#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
#include <QCoreApplication>
#include <QTimer>
#include <QDataStream>
#include "SocketClient.h"
#include "SocketServer.h"

/**
 * @brief The application class.
 *
 * During the demo a TCP socket server and a client will be created
 * and the client will be connected to the listening server.
 * If either socket (server or client) receives data,
 * that will be end up here. And here will be handled.
 *
 * The constructor receives the server and
 * the client objects as parameters.
 *
 * The dataReady signals of the SocketServer and SocketClient
 * will be connected to the serverDataReady and clientDataReady slots.
 * Both slots will print out the received data.
 * The tick slot will be connected to the signal of a QTimer
 * and it will send a "What's up, Doc?" message every time it is called.
 *
 * If the server side receives a "What's up, Doc?" string,
 * it will send back the "Everything OK" message.
 */
class Application : public QCoreApplication
{
    //The socket system won't work if our class is not a proper QObject.
    //This macro extends the class with the required QObject functionality
    Q_OBJECT

public:
    /** Constructor. Not using the command line arguments.
     * The server and client objects arrive as dependency injection.*/
    Application(int argc, char *argv[], SocketServer& server, SocketClient& client);
    ~Application() = default;

    /** Starting the demo. Starts the timer which triggers the tick.*/
    void startSending();

private:
    /** Server side communication. */
    SocketServer& server;

    /** Client side communication. */
    SocketClient& client;

    /** The timer which is responsible for the periodic sending
     * of the "What's up, Doc?" message.*/
    QTimer timer;

    /** Counter used for stop the application after 10 iteration. */
    int counter;

private slots:
    /** Slot connecto to the dataReady signal. Prints out the received message. */
    void clientDataReady(QDataStream& inStream);

    /** The slot which is connected to the server's dataReady signal.
     * Sends back the response to the "What's up, Doc?" message. */
    void serverDataReady(QDataStream& inStream);

    /** The client side sends periodically the "What's up, Doc?" message to the server. */
    void tick();
};

#endif // APPLICATION_H
