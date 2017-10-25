#pragma once
#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include <QTcpServer>
#include <QDataStream>
#include <memory>

//It is required to declare the currentConnectionSocket. Although it is only a pointer,
//therefore it is not required to be included, only to forward declare,
//because the content and the size does not matter.
class QTcpSocket;

/**
 * @brief  Wrapper object of the server side communication.
 * All function are built upon the QTcpServer type serverSocket object.
 * If a new connection has been established, the newConnection slot will be informed.
 * It then saves the newly created socket into the currentConnectionSocket and
 * connect the handlerError and the dataReceived slots.
 *
 * The data ready signal signs that a full message has been arrived.
 *
 * The established communication of the server and the client are the same.
 * The source code is doubled only for teaching purpouses.
 */
class SocketServer : public QObject
{
    //See the comment in the Application class
    Q_OBJECT

public:
    /** Constructor */
    SocketServer();
    ~SocketServer() = default;

    /** Starts the server which will listen on the given port. */
    void start(unsigned int port);

    /** Sending a text message */
    void send(QString text);

private:
    /** The QTcpServer socket which is responsible for the server side communication. */
    QTcpServer serverSocket;

    /** The socket of the currently opened socket. */
    QTcpSocket *currentConnectionSocket = nullptr;

    /** The stream used for receiving data. */
    std::unique_ptr<QDataStream> receiveStream;

    /** The size of the currently received data. */
    qint32 currentMessageSize;

signals:
    /** Emitted when a full message is received.
     * It is mandatory to read out the full message on the handler side. */
    void dataReady(QDataStream&);

private slots:
    /** The server socket signs that a new connection has been established. */
    void newConnection();

    /** Signs that the connection has been closed. */
    void disconnected();

    /** Signs that the socket encountered an error. */
    void handleError(QAbstractSocket::SocketError socketError);

    /** Data received. It is not sure that a whole message. */
    void dataReceived();
};

#endif // SOCKETSERVER_H
