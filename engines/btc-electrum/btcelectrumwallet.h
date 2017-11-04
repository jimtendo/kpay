#ifndef BTCELECTRUMWALLET_H
#define BTCELECTRUMWALLET_H

#include "engines/electrumwallet.h"

class ElectrumEngine;

class BTCElectrumWallet : public ElectrumWallet
{
public:
    BTCElectrumWallet(ElectrumEngine* engine);
};

#endif // BTCELECTRUMWALLET_H
