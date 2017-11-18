#include "mycppclass.h"
#include <QDebug>

MyCppClass::MyCppClass(QObject *parent) : QObject(parent)
{

}

void MyCppClass::buttonClicked()
{
    qDebug()<<"Button Clicked.";

    QVariant variant("Button clicked");

    emit updateButtonText(variant);

    emit updateText();
}
