#include "kpaymainwindow.h"

#include "engineprovider.h"
#include "engineinterface.h"
#include "walletinterface.h"

#include "engines/btc-electrum/btcelectrumengine.h"
#include "engines/ltc-electrum/ltcelectrumengine.h"

#include <QDir>
#include <QStandardPaths>
#include <QPluginLoader>
#include <QQmlContext>
#include <QDebug>

KPayMainWindow::KPayMainWindow(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setApplicationDisplayName(tr("KPay"));
    setApplicationVersion("0.1");

    // Setup Tray Icon
    trayIcon = new QSystemTrayIcon(QIcon::fromTheme("bitcoin"), this);
    trayIcon->show();

    // Lets make sure a folder for our application data exists
    QDir baseDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    baseDir.mkpath(".");

    // Create QML Engine
    m_qmlEngine = new QQmlApplicationEngine(this);
    
    // Create Engine Provider Singleton and register it
    qmlRegisterSingletonType<EngineProvider>("org.kde.kpay.engineprovider", 1, 0, "EngineProvider", EngineProvider::SingletonProvider);
    m_engineProvider = EngineProvider::singleton();
    m_engineProvider->addEngine(new BTCElectrumEngine);
    m_engineProvider->addEngine(new LTCElectrumEngine);
    
    // Start each engine
    foreach (EngineInterface *engine, m_engineProvider->engines()) {
        engine->start();
    }

    // Register types
    qmlRegisterType<EngineInterface>("org.kde.kpay.engineinterface", 1, 0, "EngineInterface");
    qmlRegisterType<WalletInterface>("org.kde.kpay.walletinterface", 1, 0, "WalletInterface");
    
    // Load QML
    m_qmlEngine->load(QUrl("qrc:/qml/main.qml"));
}

KPayMainWindow::~KPayMainWindow()
{

}
