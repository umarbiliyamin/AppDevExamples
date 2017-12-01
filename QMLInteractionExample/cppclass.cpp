#include "cppclass.h"
#include <QDebug>
#include <QString>

CppClass::CppClass(QObject *parent) : QObject(parent)
{

}

void CppClass::myFunction(QString text)
{
    qDebug()<< text;
}
