#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>

class CppClass : public QObject
{
    Q_OBJECT
public:
    explicit CppClass(QObject *parent = nullptr);

signals:

public slots:
    void myFunction(QString text);
};

#endif // CPPCLASS_H
