#pragma once
#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <memory>
#include <QTcpSocket>
#include <QDataStream>

/**
 * @brief Wrapper object of the client side communication.
 * All function are built upon the QTcpSocket type socket object.
 *
 * The established communication of the server and the client are the same.
 * The source code is doubled only for teaching purpouses.
 */
class SocketClient : public QObject
{
    //See the comment in the Application class
    Q_OBJECT

public:
    /** Konstruktor. */
    SocketClient();
    ~SocketClient() = default;

    /** Builds up the connection with the server and connects the signals
     * of the socket to the handlerError and dataReceived slots.
     * Also creates the receiveStream and binds it to the socket. */
    void connect(QString url, int port);

    /** Sends a text message over the socket.*/
    void send(QString text);

private:
    /** The underlying QTcpSocket instance. */
    QTcpSocket socket;

    /** The stream which is used for storing the received data.
     * The connect function instantiates and connects it to the socket */
    std::unique_ptr<QDataStream> receiveStream;

    /** The size of the currently received packet.
     * It is required because it can happen,
     * that only a part of a message arrives during a dataReceived call. */
    qint32 currentMessageSize;

signals:
    /** Akkor emittálódik, amikor egy teljes üzenet beérkezett.
     * Fontos, hogy a kezelő oldal ürítse is ki a QDataStreamet. */

    /** Emitted when a full message is received.
     * It is mandatory to clear the QSocketStream on the handler side. */
    void dataReady(QDataStream&);

private slots:
    /** Handling socket errors.*/
    void handleError(QAbstractSocket::SocketError socketError);
    /** Handling the receiving of data on the socket. */
    void dataReceived();
};

#endif // SOCKETCLIENT_H
