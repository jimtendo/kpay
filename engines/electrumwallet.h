#ifndef ELECTRUMWALLET_H
#define ELECTRUMWALLET_H

#include "walletinterface.h"

class ElectrumEngine;

#include <QJsonDocument>

class ElectrumWallet : public WalletInterface
{
public:
    ElectrumWallet(ElectrumEngine* engine);

    virtual QString name();
    virtual QString icon();

    void setName(QString name);
    void setIcon(QString name);

public slots:
    void handleJson(QJsonDocument json);

private:
    ElectrumEngine *m_engine;

    QString m_name;
    QString m_icon;

    QHash<QString, int> m_addresses;
};

#endif // ELECTRUMWALLET_H
