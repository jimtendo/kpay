import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.0 as Kirigami

Kirigami.Page {
    title: "Bitcoin"
    actions {
        main: Kirigami.Action {
            iconName: "settings"
            onTriggered: {
                print("Action button in buttons page clicked");
                sheet.sheetOpen = !sheet.sheetOpen
            }
        }
    }
    GridLayout {
        rows: 4
        anchors.fill: parent
        columns: 1
        height:500
      
        GridLayout {
            Layout.alignment: Qt.AlignHCenter
            width: parent.width
            columns: 3
            columnSpacing: 40
          
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Balance"
                    level: 2
                }
                
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "0.00BTC"
                    level: 1
                }
            }
            
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Value"
                    level: 2
                }
                
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "$0USD"
                    level: 1
                }
            }
            
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Pending"
                    level: 2
                }
                
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignHCenter
                    text: "0.00BTC"
                    level: 1
                }
            }
        }

        GridLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            columns:2
            rows:1
            Button {
                Layout.fillWidth: true
                text: "Receive"
            }
            Button {
                Layout.fillWidth: true
                text: "Send"
            }
        }

        Kirigami.Separator { }
        RowLayout {
            ListModel {
                id: transactionsModel
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
                ListElement {
                    date: "1/1/2017"
                    amount: "0.1BTC"
                    value: "$1000"
                    confirmations: 1
                }
            }
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                ListView {
                    id: transactionsView
                    anchors.fill: parent
                    model: transactionsModel
                    header: TransactionsDelegate {
                        date: "Date"
                        amount: "Amount"
                        value: "Value"
                        confirmations: "Confirmations"
                    }
                    delegate: TransactionsDelegate {
                        date: model.date
                        amount: model.amount
                        value: model.value
                        confirmations: model.confirmations
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
}
