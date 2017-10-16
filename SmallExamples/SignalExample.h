#pragma once
#ifndef SIGNALEXAMPLE_H
#define SIGNALEXAMPLE_H
#include <QObject>
#include <QDebug>

class SignalExample : public QObject
{
    Q_OBJECT
public:
    SignalExample();
    ~SignalExample();

    void start()
    {
        emit mySignal(5);
    }

signals:
    void mySignal(int szam);

public slots:
    void mySlot(int szam)
    {
        qDebug() << "Signal received:" << szam << endl;
    }
};

#endif // SIGNALEXAMPLE_H
