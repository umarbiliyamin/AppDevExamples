#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

//
void NetworkManager::myReplyFinished(QNetworkReply*reply)
{
    QByteArray webData = reply->readAll();

    QList<QPair<QString,QString>> graphValues;

    //QString webDataString = QString(webData);

    QJsonDocument document = QJsonDocument::fromJson(webData);

    if(document.isArray() == true){
        //retreive the array
        QJsonArray rootArray = document.array();
    }

    else if(document.isObject() == true)
    {

        QJsonObject rootObject = document.object();

        QJsonObject timeSeries = rootObject["Time Series (Daily)"].toObject();
        QStringList keys = timeSeries.keys();
        for (QString k : keys){
            QJsonObject dayValues = timeSeries[k].toObject();
            QString openValue =  dayValues["1. open"].toString();

            QPair<QString,QString> dataItem;
            dataItem.first = k;
            dataItem.second = openValue;

            graphValues.append(dataItem);
        }

/*
        QStringList keys = rootObject.keys();
        for (QString k : keys){


            if(rootObject[k].isObject() == true){
                QJsonObject object = rootObject[k].toObject();

                for (QString childkey : object.keys()){
                    qDebug() << childkey;
                }
            }
        }
*/
    }

    for (int i=0; i<graphValues.size(); i++){
        QPair<QString,QString> data = graphValues[i];
        qDebug()<<data.first <<" - "<<data.second;
    }


    //qDebug()<<webDataString;
}
