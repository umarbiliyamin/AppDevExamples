#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include "SocketServer.h"

SocketServer::SocketServer()
    : QObject(nullptr), receiveStream(nullptr), currentMessageSize(0)
{
}

void SocketServer::start(unsigned int port)
{
    // The server socket opens the port.
    if (!serverSocket.listen(QHostAddress::Any, port))
    {
        qWarning() << "SocketServer::Start: Opening server socket failed: ";
        qWarning() << serverSocket.errorString();
    }
    else
    {
        qWarning() << "SocketServer::Start: The server socket is waiting for incomming connections...";
    }

    // We connect the newConnection slot.
    connect(&serverSocket, &QTcpServer::newConnection, this, &SocketServer::newConnection);
}

void SocketServer::newConnection()
{
    qDebug() << "SocketServer::newConnection: Incomming connection...";

    //Grabbing the communication socket from the server socket.
    QTcpSocket *newSocket = serverSocket.nextPendingConnection();
    if (newSocket)
    {
        // Connecting the disconnected slot.
        connect(newSocket, &QTcpSocket::disconnected, this, &SocketServer::disconnected);

        //If we have a previously active differenct socket we should disconnect
        if (currentConnectionSocket != nullptr && newSocket != currentConnectionSocket)
        {

            qDebug() << "SocketServer::newConnection: Disconnecting the signals of previous connection.";

            QObject::disconnect(currentConnectionSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(CommunicationTcpSocket::handleError(QAbstractSocket::SocketError)));
            QObject::disconnect(currentConnectionSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
        }
        qDebug() << "SocketServer::newConnection: Connecting the signals of the new connection.";
        // Saving the socket.
        currentConnectionSocket = newSocket;
        connect(currentConnectionSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
        connect(currentConnectionSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));

        // Creating the data receve stream and connect it to the socket.
        receiveStream = std::make_unique<QDataStream>(currentConnectionSocket);

        qWarning() << "SocketServer::newConnection: Connection established.";
    }
}

void SocketServer::disconnected()
{
    qWarning() << "SocketServer::disconnected:";
}

void SocketServer::dataReceived()
{
    qDebug() << "SocketClient::dataReceived:";

    QDataStream &inStream = *receiveStream;
    QIODevice *socket = inStream.device();

    if (currentMessageSize == 0) {
        // New message begins.
        // We don't know the size of the message yet.
        if (socket->bytesAvailable() < (int) sizeof(qint32)) {
            // Even the size of the message has not been arrived
            return;
        }

        // Reading the size of the message.
        inStream >> currentMessageSize;
    }
    // Now we know the size of the message.

    if (socket->bytesAvailable() < (int) (currentMessageSize - sizeof(qint32))) {
        // The full message hasn't been arrived yet.
        return;
    }

    /* Signal that new message has been arrived. We pass the data after size.*/
    emit dataReady(inStream);

    // It is possible that we received parts of another message too.
    currentMessageSize = 0;
    if (socket->bytesAvailable() > 0) {
        /* By using the QTimer-t we call this slot again to process the remaining
         * received bytes. */
        QTimer::singleShot(0, this, SLOT(dataReceived()));
    }
}

void SocketServer::handleError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "SocketServer::handleError: " << socketError;
}

void SocketServer::send(QString text)
{
    //Buffer for sending data
    //It is required only for sending therefore we create it here.
    QByteArray sendBuffer;

    //We create a stream by with we can write into the buffer
    //It is hard to create a stream, since i.e. they cannot be copied.
    auto stream = std::unique_ptr<QDataStream>(new QDataStream(&sendBuffer, QIODevice::WriteOnly));

    //The beginning of the message contains the size which should be determinded.
    //We save where we stay in stream
    const qint64 startPos = stream->device()->size();
    // Lefting out the place of the size
    // If we got the size, we come back and overwrite it.
    qint32 msgSize = 0;
    *stream << msgSize;

    // Now we write the message to the stream.
    *stream << text;

    // We save where we stay in the stream.
    const qint64 endPos = stream->device()->size();

    // We seek back to the place of the message-size and set it.
    stream->device()->seek(startPos);
    msgSize = endPos - startPos;
    *stream << msgSize;

    // Than we seed forth to the previous position.
    stream->device()->seek(endPos);

    // Sending out the content of the stream.
    qDebug() << "SocketServer::send(): " << sendBuffer.size() << " byte:\n" << sendBuffer.toHex();
    currentConnectionSocket->write(sendBuffer);
    sendBuffer.clear();
}
