#ifndef CUSTUMTICKER_H
#define CUSTUMTICKER_H

#include <QObject>

//In order to use QTimer
#include <QTimer>

//In order to use the valueUpdated function
#include <QVariant>

//to use the QList
#include <QList>

class CustumTicker : public QObject
{
    Q_OBJECT
private:
    QTimer* ticker;
    float timeStamp;

    QList<QObject*> m_dataItems;

public:
    explicit CustumTicker(QObject *parent = nullptr);

    QList<QObject*> dataItems() const
    {
        return m_dataItems;
    }

    Q_PROPERTY(QList<QObject*> dataItems READ dataItems WRITE setDataItems NOTIFY dataItemsChanged)

    void setDataItems(const QList<QObject*> &dataItems);

signals:
    void tick();
    void valueUpdated(QVariant x, QVariant y);
    void dataItemsChanged();

public slots:
    void timerTick();
};

#endif // CUSTUMTICKER_H
