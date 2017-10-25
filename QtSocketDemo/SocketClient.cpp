#include <QObject>
#include <QDebug>
#include <QTimer>
#include <memory>
#include "SocketClient.h"

SocketClient::SocketClient()
    : QObject(nullptr), currentMessageSize(0)
{
}

void SocketClient::connect(QString url, int port)
{
    qDebug() << "SocketClient::connect: Connecting to the server...";
    socket.connectToHost(url, port, QIODevice::ReadWrite);

    qDebug() << "SocketClient::connect: Connecting socket signals.";
    QObject::connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    receiveStream = std::make_unique<QDataStream>(&socket);

    qWarning() << "SocketClient::connect: The new connection is up.";
}

void SocketClient::handleError(QAbstractSocket::SocketError socketError)
{
    qWarning() << "SocketClient::handleError: " << socketError;
}

void SocketClient::dataReceived()
{
    qDebug() << "SocketClient::dataReceived: ";

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

void SocketClient::send(QString text)
{
    //Buffer for sending data
    //It is required only for sending therefore we create it here.
    QByteArray sendBuffer;

    //We create a stream by with we can write into the buffer
    //It is hard to create a stream, since i.e. they cannot be copied.
    auto stream = std::unique_ptr<QDataStream>(new QDataStream(&sendBuffer, QIODevice::WriteOnly));

    //The beginning of the message contains the size which should be determinded.
    //We save where we stay in stream.
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
    qDebug() << "SocketClient::send(): " << sendBuffer.size() << " byte:\n" << sendBuffer.toHex();
    socket.write(sendBuffer);
    sendBuffer.clear();
}
