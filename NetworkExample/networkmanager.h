#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT

    QNetworkAccessManager* manager;

public:
    explicit NetworkManager(QObject *parent = 0);
    void loadWebPage();

signals:

public slots:
    void myReplyFinished(QNetworkReply* reply);
};

#endif // NETWORKMANAGER_H
