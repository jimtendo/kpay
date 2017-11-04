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

#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H

#include <QObject>
#include <QString>
#include <QQmlEngine>

#include "walletinterface.h"

class EngineInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString icon READ icon)
    Q_PROPERTY(QString addWalletQmlPath READ addWalletQmlPath)
    Q_PROPERTY(QQmlListProperty<WalletInterface> wallets READ qmlWallets NOTIFY walletsUpdated)
    
public:
    EngineInterface(QObject* parent = 0);
    ~EngineInterface();

    virtual bool start() {
        return true;
    }
    
    virtual bool stop() {
        return true;
    }
    
    virtual QString name() {
        return QString();
    }

    virtual QString icon() {
        return QString();
    }

    virtual QString addWalletQmlPath() {
        return QString();
    }

    QList<WalletInterface*> wallets() {
        return m_wallets;
    }

    QQmlListProperty<WalletInterface> qmlWallets();
    
signals:
    void walletsUpdated();

protected:
    QList<WalletInterface*> m_wallets;
};

#endif // ENGINEINTERFACE_H
