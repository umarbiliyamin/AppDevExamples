#ifndef MYCPPCLASS_H
#define MYCPPCLASS_H
#include <QObject>
#include <QVariant>

class MyCppClass : public QObject
{
    Q_OBJECT
public:
    explicit MyCppClass(QObject *parent = 0);

signals:
    void updateButtonText(QVariant);
    void updateText();

public slots:
    void buttonClicked();
};

#endif // MYCPPCLASS_H
