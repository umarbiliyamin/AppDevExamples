#ifndef COLORITEM_H
#define COLORITEM_H

#include <QObject>

class ColorItem : public QObject
{
    Q_OBJECT
private:
    QString m_name;
    QString m_colorCode;

public:
    explicit ColorItem(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString colorCode() const;
    void setColorCode(const QString &colorCode);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString colorCode READ colorCode WRITE setColorCode NOTIFY colorCodeChanged)

signals:
    void nameChanged();
    void colorCodeChanged();

public slots:
};

#endif // COLORITEM_H
