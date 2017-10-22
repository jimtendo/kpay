# KPay

## Overview

KPay is intended to be a cryptocurrency multi-wallet built specifically for the KDE Platform. The interface will be written in QML (with Kirigami) so that in future Plasma Mobile can be supported.

## Architecture

KPay intends to be plugin-based so that other coins (or payment methods) can easily be integrated. A plugin is called an "Engine". An "Engine" can support several different currencies (BTC, LTC, etc).

All of these Engines would belong to a "Backend" C++ singleton that is exposed to QML.

```C++
class Backend {
    ...
    /* QML frontend can loop through each engine to get list of wallets instantiated.
     * QML frontend can loop through each engine to get list of wallets supported (when adding a new wallet
     */
    QQmlListProperty<Engine*> engines;
    ...
}
```

To illustrate how an Engine may work, KPay might have an engine called "Blockcypher" that is built to leverage www.blockcypher.com's API's (in practice this might not be a good idea as we will probably run into API rate-limiting). Blockcypher supports several different cryptocurrencies, including BTC, LTC, Dash and Ethereum. The interface for each of these currencies will be called a "Wallet".

Blockcypher (Engine)
- Bitcoin (Wallet)
- Litecoin (Wallet)
- Ethereum (Wallet)
- Dash (Wallet)

The interface for an Engine will probably look something like the following:
```C++
class Engine {
    - virtual QQmlListProperty<QString> walletsSupported(); // List of wallets supported (e.g. "Bitcoin (Blockcypher)")
    - virtual QQmlListProperty<Wallet*> wallets(); // List of wallets instantiated
    - virtual signal void walletsUpdated(); // Used to trigger Frontend Refresh when new Wallet instantiated
}
```

The interface for a Wallet will probably look something like the following:
```C++
class Wallet {
    virtual QString type();  // Wallet Type (e.g. "Bitcoin")
    virtual QString name();  // Wallet Nickname (e.g. "Bitcoin Spending Account")
    
    /* The "start" and "stop" methods will be used to start and stop a background worker for that
     * wallet. For example, the worker for Blockcypher may just be a Timer that polls the addresses
     * using Blockcyphers' API every 30 seconds to check for new transactions. Some other engines
     * might contain SPV clients.
     */
    virtual bool start();
    virtual bool stop();
    
    /* The *QmlPath methods will return a path that contains the QML for those parts of the UI.
     * Extendable Base versions of these QML UI's will most likely be provided by KPay to ease
     * development and provide a consistent UI across different Wallets.
     */
    virtual QString overviewQmlPath();
    virtual QString viewTxQmlPath();
    virtual QString sendTxQmlPath();
    virtual QString receiveTxQmlPath();
    virtual QString settingsQmlPath();
}
```

### An example of how a Wallet might extend the Base QML provided

```
// Blockcypher/BTC/Overview.qml
import org.kde.kpay.blockcypher.btc 1.0

WalletOverview {
  availableBalance: BlockcypherBTCWallet.availableBalance
  availableValue: BlockcypherBTCWallet.availableValue
  totalBalance: BlockcypherBTCWallet.totalBalance
  totalValue: BlockcypherBTCWallet.totalValue
  transactions: BlockcypherBTCWallet.transactions
}

// Blockcypher/BTC/Send.qml
import org.kde.kpay.blockcypher.btc 1.0

WalletSend {
  ...
  
  onSend: function() {
    BlockcypherBTCWallet.sendTx(...)
  }
}
```

## Hardware Support

The intention is to eventually add support for Hardware Wallets like the Ledger Nano (to minimize risk of user's losing their coin).

This could be implemented with a "LedgerNanoEngine" and could use the C-API library provided by Ledger. The "Engine" interface itself could add "Wallets" when it is detected that a Ledger device has been plugged in. These would then show in the Kirigami Left Pane (Wallet List View) which would be triggered to refresh when an Engine emits the walletsUpdated() signal. Upon clicking, an extended QML interface could allow the user to select which "Account" they wish to use.

## Storing Data

Storing Data (transactions, seeds, keys, etc) would be at the discretion of an Engine itself. As a convention, it could be recommended that an SQLite Database is used and the Private Key/Seed encrypted. The "WalletOverview" QML Interface then extend could then be responsible for providing the UI for unlocking of this Wallet. C++ in the backend could then be responsible for performing the "unlocking" itself.

## Other Considerations

Blockcypher probably isn't practical as an engine due to Rate Limiting (unless a corporate plan is purchased). Currently searching for one that can provide transaction functionality (not just address-lookup functionality).
