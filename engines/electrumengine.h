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

#ifndef ELECTRUMENGINE_H
#define ELECTRUMENGINE_H

#include "engineinterface.h"

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>

class ElectrumWallet;

class ElectrumEngine : public EngineInterface
{
    Q_OBJECT
public:
    ElectrumEngine(QObject* parent = 0);
    ~ElectrumEngine();

    bool start();

    /* Returns the name of the SQLite Database that
     * should be used
     */
    virtual QString databaseName() = 0;

    /* Returns the servers to bootstrap from.
     * These should be a list of strings in the format:
     * "electrum.server.com:port"
     */
    virtual QStringList bootstrapServers() = 0;

    /* Returns an instance of the wallet that should be
     * created.
     */
    virtual ElectrumWallet *newWallet() = 0;

    /* Send a request to the primary Electrum Server */
    void sendRequest(QString method, QJsonObject parameters);

public slots:
    void connected();
    void readData();
    void handleError(QAbstractSocket::SocketError socketError);

signals:
    void receivedJson(QJsonDocument response);

protected:
    // General
    QSqlDatabase m_db;

    // Network Code
    QTcpSocket *m_tcpSocket;
    QTextStream m_in;
    QByteArray m_buffer;
    int m_requestId;

    /* Load wallets from database */
    bool loadWallets();

private:
    void writeData(QByteArray data);
};

#endif // ELECTRUMENGINE_H
