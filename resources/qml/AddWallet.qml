import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.0 as Kirigami
import org.kde.kpay.engineprovider 1.0

Kirigami.Page {
    title: "Add Wallet"

    GridLayout {
        id: gridLayout
        columns: 1
        rows: 2
        anchors.fill: parent

        Text {
            id: text1
            text: qsTr("Please select the type of wallet you would like to create below:")
            font.pixelSize: 12
        }

        ScrollView {
            id: scrollView
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                id: enginesView
                anchors.fill: parent
                model: EngineProvider.engines
                delegate: Kirigami.BasicListItem {
                    label: model.name
                    icon: model.icon
                    separatorVisible: false
                    reserveSpaceForIcon: true
                    onClicked: mainPage.setSource(model.addWalletQmlPath)
                }
                focus: true
                onCurrentIndexChanged: {
                    //var wallet = Backend.wallets[walletsView.currentIndex];

                    //console.log(wallet.name);
                }
            }
        }
    }
}
