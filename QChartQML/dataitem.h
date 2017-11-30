#ifndef DATAITEM_H
#define DATAITEM_H

#include <QObject>

class DataItem : public QObject
{
    Q_OBJECT
private:
    QString m_value1;
    QString m_value2;

public:
    explicit DataItem(QObject *parent = nullptr):QObject(parent){}

    QString value1() const{
        return m_value1;
    }

    void setValue1(const QString &value1){
        m_value1 = value1;
    }

    QString value2() const{
        return m_value2;
    }

    void setValue2(const QString &value2){
        m_value2 = value2;
    }

    Q_PROPERTY(QString value1 READ value1 WRITE setValue1 NOTIFY value1Changed)
    Q_PROPERTY(QString value2 READ value2 WRITE setValue2 NOTIFY value2Changed)

signals:
    void value1Changed();
    void value2Changed();

public slots:
};

#endif // DATAITEM_H
