#ifndef SLOTRECEIVER_H
#define SLOTRECEIVER_H

#include <QObject>
#include <QDebug>

class SlotReceiver : public QObject
{
    Q_OBJECT
public:
    explicit SlotReceiver(QObject *parent = nullptr):QObject(parent){}

signals:

public slots:
    void numberReceived(int theNumber)
    {
        qDebug()<< "the received number: "<< theNumber;
    }
};

#endif // SLOTRECEIVER_H
