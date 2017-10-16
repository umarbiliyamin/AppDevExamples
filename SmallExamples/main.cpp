#include <QtGlobal>
#include <iostream>
#include <memory>
#include <QPoint>
#include "SignalExample.h"
#include <exception>

using namespace std;

void UniquePtrExample()
{
    QPoint *first = new QPoint(2,3);
    std::unique_ptr<QPoint> second =
        std::make_unique<QPoint>(4,5);
    auto third = std::make_unique<QPoint>(6,7);
    std::cout << first->rx() << endl;
    cout << second->rx() << endl;
    cout << third->rx() << endl;
    delete first;
}

void createSignalExample()
{
    SignalExample sp;
    QObject::connect(&sp,SIGNAL(mySignal(int)),
                     &sp, SLOT(mySlot(int)));

    //QObject::connect(&sp,&SignalPelda::jelzesSignal,
    //                 &sp, &SignalPelda::jelzesSlot);
    sp.start();
    QObject::disconnect(&sp,SIGNAL(mySignal(int)),
                        &sp, SLOT(mySlot(int)));
}

class InvalidTurnException: public exception
{
public:
    InvalidTurnException(float degrees)
        : deg(degrees) { }
    float deg;
    virtual const char* what() const throw()
    {
        return "Invalid angle";
    }
};

bool isRobotOnline()
{
    return false;
}

void turn(float deg)
{
    if (deg>60)
        throw InvalidTurnException(deg);
    if (!isRobotOnline())
        throw std::runtime_error(
            "Connection error");
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    qDebug() << "UniquePtr example:";
    UniquePtrExample();
    qDebug() << "Signal example:";
    createSignalExample();
    qDebug() << "Exception example:";
    try
    {
        turn(70);
    }
    catch (InvalidTurnException& ite)
    {
        qDebug() << ite.what();
        qDebug() << "Angle: " << ite.deg;
    }
    catch (std::runtime_error& e)
    {
        qDebug() << e.what();
    }
    catch (...)
    {
        qDebug() << "Something went wrong. :(";
    }

    return 0;
}
