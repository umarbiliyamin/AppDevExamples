#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(myReplyFinished(QNetworkReply*)));
}

void NetworkManager::loadWebPage(){
    QNetworkRequest request;

    QString apiKey = "demo";
    QString urlString = QString("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=%0").arg(apiKey);

    QUrl url(urlString);

    request.setUrl(url);

    QNetworkReply *reply = manager->get(request);

}



void NetworkManager::myReplyFinished(QNetworkReply *reply)
{
    QByteArray webData = reply->readAll();
    QString webDataString = QString(webData);
    qDebug()<<webDataString;
}
