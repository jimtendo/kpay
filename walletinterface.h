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

#ifndef WALLETINTERFACE_H
#define WALLETINTERFACE_H

#include <QObject>
#include <QString>

class WalletInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameUpdated)
    Q_PROPERTY(QString icon READ icon NOTIFY iconUpdated)
    Q_PROPERTY(QString overviewQmlPath READ overviewQmlPath)
    Q_PROPERTY(QString sendQmlPath READ sendQmlPath)
    Q_PROPERTY(QString receiveQmlPath READ receiveQmlPath)
    Q_PROPERTY(QString settingsQmlPath READ settingsQmlPath)
public:


    virtual QString name() {
        return QString();
    }
    
    virtual QString icon() {
        return QString();
    }
    
    virtual QString overviewQmlPath() {
        return QString();
    }
    
    virtual QString sendQmlPath() {
        return QString();
    }
    
    virtual QString receiveQmlPath() {
        return QString();
    }
    
    virtual QString settingsQmlPath() {
        return QString();
    }
    
signals:
    void nameUpdated();
    void iconUpdated();

private:
};

#endif // WALLETINTERFACE_H
