#ifndef SIGNALEMITTER_H
#define SIGNALEMITTER_H

#include <QObject>

class SignalEmitter : public QObject
{
    Q_OBJECT
public:
    explicit SignalEmitter(QObject *parent = nullptr):QObject(parent){};

signals:
    void exampleSignal(int number);
public slots:
};

#endif // SIGNALEMITTER_H
