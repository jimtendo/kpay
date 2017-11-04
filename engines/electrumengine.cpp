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

#include "electrumengine.h"
#include "electrumwallet.h"

#include <QJsonDocument>
#include <QtSql/QSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

ElectrumEngine::ElectrumEngine(QObject* parent)
        : EngineInterface(parent)
        , m_tcpSocket(new QTcpSocket(this))
        , m_requestId(1)
{
    // This is the TextStream we'll receive TCP Socket data into
    m_in.setDevice(m_tcpSocket);

    // Connect Signals and Slots
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
}

ElectrumEngine::~ElectrumEngine()
{

}

bool ElectrumEngine::start()
{
    // Attempt to load wallets
    if (!loadWallets()) {
        qCritical() << databaseName() << " could not load wallets.";
        return false;
    }

    // Cancel any previous requests (if they exist)
    m_tcpSocket->abort();

    // Connect to host
    m_tcpSocket->connectToHost("VPS.hsmiths.com", 50001);

    return true;
}

void ElectrumEngine::sendRequest(QString method, QJsonObject parameters)
{
    // Compile request
    QJsonObject request
    {
        {"id", m_requestId},
        {"jsonrpc", "2.0"},
        {"method", method},
        {"params", parameters}
    };

    // Put into QJsonDocument so we can serialize it and send
    QJsonDocument serializable(request);
    writeData(serializable.toJson(QJsonDocument::Compact)+'\n');

    // Increment the request id
    m_requestId++;
}

void ElectrumEngine::connected()
{
    qInfo() << "Connected to server";

    sendRequest("server.version", QJsonObject());
    sendRequest("blockchain.address.get_history", QJsonObject{
                    {"address", "1GxF7gdFaqQ6PMVzZ542FVJrtH8TbRcTj5"}
                });
}

void ElectrumEngine::writeData(QByteArray data)
{
    if(m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->write(data);
        m_tcpSocket->waitForBytesWritten();
    } else {
        qInfo() << "You've pre-emptively tried to write data because you're stupid.";
    }
}

void ElectrumEngine::readData()
{
    // Read in data from socket
    m_buffer.append(m_in.readAll());

    // Try to convert packet to JSON
    QJsonDocument json = QJsonDocument::fromJson(m_buffer);

    // If it could be converted, send to all child wallets
    if (!json.isNull()) {
        emit receivedJson(json);
        m_buffer.clear();
    }
}

void ElectrumEngine::handleError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qWarning() << tr("The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qWarning() << tr("The connection was refused by the server.");
        break;
    default:
        qWarning() << tr("The following error occurred: %1.").arg(m_tcpSocket->errorString());
    }
}

bool ElectrumEngine::loadWallets()
{
    // Load existing wallets from database
    m_db = QSqlDatabase::addDatabase("QSQLITE", databaseName());
    m_db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
                         QDir::separator() +
                         databaseName()+".sqlite");

    // If we could not open database...
    if (!m_db.open()) {
        qWarning() << databaseName() << ": " << m_db.lastError().text();
        return false;
    }

    // Define migrations
    QStringList migrations;
    migrations << ":/btc-electrum/migrations/V0.1.sql";

    // Perform migrations if necessary
    foreach (QString migration, migrations) {
        QSqlQuery migrationRecord("SELECT * FROM migrations WHERE name LIKE '"+migration+"'", m_db);

        // Check to see if migration has been done
        if (!migrationRecord.first()) {
            QFile migrationFile(migration);

            // If we couldn't open the file, don't proceed
            if (!migrationFile.open(QIODevice::ReadOnly)) {
                qWarning() << databaseName() << ": " << migrationFile.errorString();
                return false;
            }

            // Read migration data from the file
            QStringList statements = QTextStream(&migrationFile).readAll().split(';', QString::SkipEmptyParts);

            // Loop through statements (SQLite Driver can only do one statement at a time)
            foreach (QString statement, statements) {
                if (statement.trimmed().isEmpty()) {
                    continue;
                }

                // Execute that SQL
                QSqlQuery result(statement, m_db);

                // Check if there were any errors
                if (result.lastError().type() != QSqlError::NoError) {
                    qWarning() << databaseName() << ": " << result.lastError().text();
                    return false;
                }
            }

            // Add this migration to the migrations table
            QSqlQuery insertMigration("INSERT INTO migrations VALUES ('"+migration+"');", m_db);
            if (insertMigration.lastError().type() != QSqlError::NoError) {
                qWarning() << databaseName() << ": " << insertMigration.lastError().text();
                return false;
            }
        }
    }

    // Load the wallets into memory
    QSqlQuery walletsQuery("SELECT * FROM wallets", m_db);
    while (walletsQuery.next()) {
        // Create wallet
        ElectrumWallet* wallet = newWallet();
        wallet->setName(walletsQuery.value(1).toString());

        // Add wallet
        m_wallets.append(wallet);
        emit walletsUpdated();
    }

    return true;
}
