import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.0 as Kirigami
import org.kde.kpay.engineprovider 1.0
import org.kde.kpay.engineinterface 1.0
import org.kde.kpay.walletinterface 1.0

Kirigami.ApplicationWindow {
    id: root

    property string pTitle: "Plasma Pay"
    property string pIcon: ":/icons/icon.png"
    property string pBanner: "/img/banner.png"
    property var pMenu: []

    header: Kirigami.ApplicationHeader {}
    globalDrawer: Kirigami.GlobalDrawer {
        bannerImageSource: pBanner
        GridLayout {
            anchors.fill: parent
            columns: 1
            rows: 2
            ListView {
                id: walletsView
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: EngineProvider.wallets
                delegate: Kirigami.BasicListItem {
                    label: model.name
                    icon: model.icon
                    separatorVisible: false
                    reserveSpaceForIcon: true
                    onClicked: {
                        walletsView.currentIndex = model.index
                        console.log(model.name+model.icon)
                    }
                }
                focus: true
                onCurrentIndexChanged: {
                    console.log(model.name);
                }
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Add Wallet")
                onClicked: mainPage.setSource("AddWallet.qml")
            }
        }
    }
    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: Loader {
        id: mainPage
        source: "WalletOverview.qml"
        asynchronous: true
        visible: status == Loader.Ready
    }

    function loadWallet(walletId) {
        pTitle = walletId;
    }
}
