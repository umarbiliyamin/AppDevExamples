#include <QGuiApplication>

//included to support QtCharts
#include <QApplication>

#include <QQmlApplicationEngine>
#include "custumticker.h"

//for the setContextProperty
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //Replaced QGuiApplication to support QtCharts
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    CustumTicker* myTicker = new CustumTicker();

    engine.rootContext()->setContextProperty("cppTicker",myTicker);

    return app.exec();
}
