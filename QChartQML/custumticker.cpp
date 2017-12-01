#include "custumticker.h"
#include <math.h>
#include "dataitem.h"

void CustumTicker::setDataItems(const QList<QObject *> &dataItems)
{
    m_dataItems = dataItems;
}

CustumTicker::CustumTicker(QObject *parent) : QObject(parent)
{
    timeStamp = 0.0f;
    ticker = new QTimer();
    connect(ticker,SIGNAL(timeout()),this,SLOT(timerTick()));
    ticker->start(30);

    DataItem* item1 = new DataItem();
    item1->setValue1("value1_1");
    item1->setValue2("value2_1");

    DataItem* item2 = new DataItem();
    item2->setValue1("value1_2");
    item2->setValue2("value2_2");

    m_dataItems.append(item1);
    m_dataItems.append(item2);
}

void CustumTicker::timerTick()
{
    emit tick();

    timeStamp += 0.03;

    float x = timeStamp;
    float y = sin(timeStamp);

    emit valueUpdated(QVariant(x),QVariant(y));
}
