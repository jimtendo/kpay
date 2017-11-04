#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <qglobal.h>
#include <QString>
#include <QDebug>
#include <QPluginLoader>

#include "kpaymainwindow.h"

#include "walletinterface.h"
#include "engineinterface.h"

#include "utils.h"

int main(int argc, char* argv[])
{
    // Create lock file so that only one instance of app can run
    QString tmpDir = QDir::tempPath();
    QLockFile lockFile(tmpDir + "/kpay.lock");

    // Check to see if app is already running
    if (!lockFile.tryLock(100)){
        qInfo() << "KPay is already running.";
        return 0;
    }

    KPayMainWindow app(argc, argv);
    return app.exec();
}
