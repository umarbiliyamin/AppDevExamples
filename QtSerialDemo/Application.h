#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
#include <QCoreApplication>
#include <QTimer>
#include <QDataStream>
#include "CommunicationSerialPort.h"

/**
 * @brief The Application class.
 *
 * This demo postulates that there is a loopback device on the COM5 ports which act as an echo service
 *
 * During the demo there will be established a serial connection through all the sent data will be received
 * as echo messages
 *
 * It gets the communication object through constructor parameter which will be used during the demo
 *
 * It connects the dataReady slot with dataReady signal of the CommunicationSerialPort
 * and the tick slot with a QTimer.
 *
 * The dataReady will log when data is received and the tick will send a "What's up, doc?" message.
 */
class Application : public QCoreApplication
{
    // The socket architecture won't work if our QObject class is not proper.
    // This macro extends the class with the required functionality of the QObject of Qt.
    Q_OBJECT

public:
    /** Constructor. Not using the command line arguments. The server and client arrives
     * through dependecy injection. */
    Application(int argc, char *argv[], CommunicationSerialPort& serialPort);
    ~Application() = default;

    /** Starting of the Demo. Starts the timer, which will trigger the tick. */
    void startSending();

private:
    /** Serial communication */
    CommunicationSerialPort& serialPort;

    /** The timer which responsible for initiating the periodic "What's up, doc?" message. */
    QTimer timer;

    /** Counter for stop the application after 10 message. */
    int counter;

private slots:
    /** The slot which is connected to the dataReady signal of the serialPort. Displays the received message. */
    void dataReady(QDataStream& inStream);

    /** Periodically sends the  "What's up, doc?" messages. */
    void tick();
};

#endif // APPLICATION_H
