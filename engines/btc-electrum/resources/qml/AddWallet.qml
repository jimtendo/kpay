import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.0 as Kirigami
import org.kde.kpay.engineprovider 1.0

Kirigami.Page {
    title: "Add Wallet test test test"

    GridLayout {
        id: gridLayout
        columns: 1
        rows: 3
        anchors.fill: parent

        Button {
            id: button1
            text: qsTr("New Wallet")
            Layout.minimumHeight: 75
            Layout.minimumWidth: 250
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: button
            text: qsTr("Restore/Import")
            Layout.minimumHeight: 75
            Layout.minimumWidth: 250
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: button2
            text: qsTr("Watch Address")
            Layout.minimumHeight: 75
            Layout.minimumWidth: 250
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }


    }
}
