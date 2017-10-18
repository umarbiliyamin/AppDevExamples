#pragma once
#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <memory>
#include <QDataStream>
#include <QDateTime>

/**
 * @brief Stream based communication class.
 *
 * After instatiation the inner data receive stream can
 * be connected to the device by the connectToDevice
 * method.
*/
class Communication : public QObject
{
    Q_OBJECT

public:
    /** constructor */
    Communication();
    virtual ~Communication();

    /** Connec to a device (i.e. QTcpSocket), which it will use. */
    void connectToDevice(QIODevice *device);

    /** Returns if the is an opened connection. */
    virtual bool isConnected() const = 0;

    /** Returns a pointer to the data receive stream. */
    QDataStream *getReceiveStream();

    /** Sends the content of an object: writes into the sendBuffer, than calls the
     * sendBufferContent() method.
     *
     * By this method every oject can be sent, which can be written into a QDataStream by
     * using the operator<<.
     * Note: In this way there is no need for a superclass from which the sendable data classes should be inherited
     */
    template<typename T>
    void send(const T& toSendObject)
    {
        auto stream = getSendStream();

        // saving the curent stream position
        const qint64 startPos = stream->device()->size();
        qint32 msgSize = 0;
        // Initally the message size will be 0.
        // However, when we will know the exact size, we will overwrite it.
        *stream << msgSize;
        //
        *stream << toSendObject;
        const qint64 endPos = stream->device()->size();

        // Jumping back and setting the message size to the correct value.
        stream->device()->seek(startPos);
        msgSize = endPos - startPos;
        *stream << msgSize;
        // Juping forth to the end of the message
        stream->device()->seek(endPos);

        // Sending out the message
        //  (This is an abstract method, each protocol should implement according to their needs.)
        sendBufferContent();
    }

signals:
    /** Error notification. */
    // Each protocol should connect it properly.
    void errorOccurred(const QString&);

    /** A full message arrived */
    void dataReady(QDataStream& stream);

protected:
    /** Stream for receiving data. Setted by the connectToDevice(). */
    QDataStream *receiveStream;

    /**
     * Before sending out all data will be stored temporarly here
     * Can be reached through the getSendStream() method. */
    QByteArray sendBuffer;

    /**
     * Gives back a stream, which writes the data to the sendBuffer
     * Only the sendBufferContent() method should be called afterward.
     * From outside the send() method should be used, that will call this method. */
    std::unique_ptr<QDataStream> getSendStream();

    /**
     * Sends out the content of the buffer. The child classes should implement it a
     * according to their protocol. */
    virtual void sendBufferContent() = 0;

private:
    /** The size of the currently under receiving message. Used by the dataReceived() slot. */
    qint32 currentMessageSize;

protected slots:
    /** Part of a message received
     * The child classes use this method to sign that data is received
     */
    void dataReceived();
};

#endif // COMMUNICATION_H
