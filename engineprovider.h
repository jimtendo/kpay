/*
 * Copyright (c) 2017 Jim Hamill <jim.hamill@gigya-inc.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef ENGINEPROVIDER_H
#define ENGINEPROVIDER_H

#include <QObject>
#include <QList>
#include <QQmlEngine>
#include <QDebug>

#include "engineinterface.h"

class WalletInterface;

class EngineProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<EngineInterface> engines READ qmlEngines NOTIFY enginesUpdated)
    Q_PROPERTY(QQmlListProperty<WalletInterface> wallets READ qmlWallets NOTIFY walletsUpdated)
public:
    EngineProvider(QObject* parent = 0);
    ~EngineProvider();
  
    Q_INVOKABLE bool testSingleton(const QString &msg)
    {
        qDebug() << "Called the C++ method with" << msg;
        return true;
    }
    
    QList<EngineInterface*> engines()
    {
        return m_engines;
    }

    /* QML Export for Engines */
    QQmlListProperty<EngineInterface> qmlEngines()
    {
        return QQmlListProperty<EngineInterface>(this, m_engines);
    }

    QList<WalletInterface*> wallets()
    {
        return m_wallets;
    }

    /* QML Export for Wallets */
    QQmlListProperty<WalletInterface> qmlWallets()
    {
        return QQmlListProperty<WalletInterface>(this, m_wallets);
    }
    
    Q_INVOKABLE void addEngine(EngineInterface *engine)
    {
        connect(engine, SIGNAL(walletsUpdated()), this, SLOT(refreshWallets()));
        m_engines.append(engine);
        emit enginesUpdated();
    }
    
    static EngineProvider *singleton()
    {
        if (EngineProvider::m_singleton == NULL) {
            EngineProvider::m_singleton = new EngineProvider();
        }

        return m_singleton;
    }
    
    static QObject *SingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return EngineProvider::singleton();
    }

public slots:
    void refreshWallets();

signals:
    void enginesUpdated();
    void walletsUpdated();
    
private:
    static EngineProvider *m_singleton;
  
    QList<EngineInterface*> m_engines;
    QList<WalletInterface*> m_wallets;
};

#endif // ENGINEPROVIDER_H
