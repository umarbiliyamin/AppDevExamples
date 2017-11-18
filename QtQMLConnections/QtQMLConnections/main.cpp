#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlProperty>
#include <QQmlContext>
#include <QMetaObject>

#include <QObject>
#include "mycppclass.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    //get a pointer to the root object which is the loaded through qml resource file ->
    //Getting the ApplicationWindow which is also a QObject
    QObject* rootObject = engine.rootObjects()[0];

    //call the function
    QVariant returnValue;
    QVariant message = "It is working!!"; //Direct conversion from QString to QVariant
    QMetaObject::invokeMethod(rootObject,"setTextFunction", Q_RETURN_ARG(QVariant, returnValue), Q_ARG(QVariant, message));

    //set propery
    QQmlProperty::write(rootObject,"title", "C++");

    //connect a signal to the slot
    //this identifier is not the id: -> it is the objectName
    QObject* button = rootObject->findChild<QObject*>("myButton");

    MyCppClass* myClass = new MyCppClass();

    //for Connections
    engine.rootContext()->setContextProperty("myClassItem",myClass);

    QObject::connect(button,SIGNAL(clicked()),myClass,SLOT(buttonClicked()));

    //emitting a C++ signal which will handled by a QML slot
    QObject::connect(myClass,SIGNAL(updateButtonText(QVariant)),button,SLOT(onButtonClickd(QVariant)));

    //The functions declared in QML are SLOTs too, thereofre we can connect SIGNALS to them
    QObject::connect(myClass,SIGNAL(updateButtonText(QVariant)),rootObject,SLOT(setTextFunction(QVariant)));

    return app.exec();
}
