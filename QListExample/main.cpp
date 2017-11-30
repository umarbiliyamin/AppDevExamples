#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "coloritem.h"

#include <QQmlContext>
#include <QVariant>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    ColorItem *orange = new ColorItem();
    orange->setName("Orange");
    orange->setColorCode("orange");

    ColorItem *gray = new ColorItem();
    gray->setName("Gray");
    gray->setColorCode("gray");

    QList<QObject*> colors;
    colors.append(orange);
    colors.append(gray);

    //QList is not a Object -> Convert to QVariant
    engine.rootContext()->setContextProperty("colorModel",QVariant::fromValue(colors));

    return app.exec();
}
