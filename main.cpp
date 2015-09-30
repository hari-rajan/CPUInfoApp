/***
 * Main file. Initializes UI handler and loads qml
 * Author: Hari Rajan
 */

#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include "src/ccpuinfouihandler.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    if (!rootObject)
    {
        qWarning() << "rootObject invalid!";
    }
    else
    {
        CCPUInfoUIHandler * uiHandler = new CCPUInfoUIHandler(rootObject);
        Q_UNUSED(uiHandler);
    }

    return app.exec();
}
