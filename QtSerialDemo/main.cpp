#include "Application.h"
#include "CommunicationSerialPort.h"

int main(int argc, char *argv[])
{
    // A the demo is works properly when the COM5 is a loopback device!
    CommunicationSerialPort serialPort(QString("COM5"),9600,QSerialPort::Data8, QSerialPort::EvenParity, QSerialPort::OneStop);
    Application app(argc, argv, serialPort);

    serialPort.connect();

    app.startSending();

    return app.exec();
}
