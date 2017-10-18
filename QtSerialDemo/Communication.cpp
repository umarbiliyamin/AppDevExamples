#include <QTimer>
#include "Communication.h"

Communication::Communication()
    : receiveStream(nullptr), currentMessageSize(0)
{
}

Communication::~Communication()
{
    if (receiveStream != nullptr)
    {
        delete receiveStream;
        receiveStream = nullptr;
    }
}

void Communication::connectToDevice(QIODevice *device)
{
    // A fogadási adatfolyam csatlakozatotása az eszközhöz (pl. sockethez)
    if (receiveStream != nullptr)
    {
        delete receiveStream;
    }
    receiveStream = new QDataStream(device);
}

std::unique_ptr<QDataStream> Communication::getSendStream()
{
    return std::unique_ptr<QDataStream>(new QDataStream(&sendBuffer, QIODevice::WriteOnly));
}

QDataStream *Communication::getReceiveStream()
{
    return receiveStream;
}

void Communication::dataReceived()
{
    // Reading until a full message arrives
    // Than emitting a Communication::dataReady signal.
    QDataStream &inStream = *getReceiveStream();
    QIODevice *socket = inStream.device();

    if (currentMessageSize == 0) {
        // New message begins
        // We don't know the size of the message yet.
        if (socket->bytesAvailable() < (int) sizeof(qint32)) {
            // Even the size of the message has not been arrived
            return;
        }

        // Reading the size of the message
        inStream >> currentMessageSize;
    }

    // Now we know the size of the message

    if (socket->bytesAvailable() < (int) (currentMessageSize - sizeof(qint32))) {
        // The full packet hasn't been arrived yet.
        return;
    }

    /* Signal that new message has been arrived. We pass the data after the id and size.
     * In case of an array the QVector deserialize itself by containing its size. */
    emit dataReady(inStream);

    // It is possible that we received another message part
    currentMessageSize = 0;
    if (socket->bytesAvailable() > 0) {
        /* By using the QTimer-t we call this slot again to process the remaining
         * received bytes. */
        QTimer::singleShot(0, this, SLOT(dataReceived()));
    }
}
