#include "electrumwallet.h"
#include "electrumengine.h"

#include <QDebug>

ElectrumWallet::ElectrumWallet(ElectrumEngine *engine)
    : m_engine(engine)
{
    connect(engine, &ElectrumEngine::receivedJson, this, &ElectrumWallet::handleJson);
}

QString ElectrumWallet::name()
{
    return m_name;
}

QString ElectrumWallet::icon()
{
    return QString("bitcoin");
}

void ElectrumWallet::setName(QString name)
{
    this->m_name = name;
    emit nameUpdated();
}

void ElectrumWallet::handleJson(QJsonDocument json)
{
    qInfo() << "CONNECTED BITCH!" << json.toJson();
}
