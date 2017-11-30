#include <QCoreApplication>

#include "signalemitter.h"
#include "slotreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SignalEmitter emitter;
    SlotReceiver receiver;

    QObject::connect(&emitter,SIGNAL(exampleSignal(int)),&receiver,SLOT(numberReceived(int)));

    emitter.exampleSignal(22);


    //Alternative solution
    SignalEmitter *emitterPointer = new SignalEmitter();
    SlotReceiver *receiverPointer = new SlotReceiver();

    QObject::connect(emitterPointer,SIGNAL(exampleSignal(int)),receiverPointer,SLOT(numberReceived(int)));

    emitterPointer->exampleSignal(23);

    return a.exec();
}
