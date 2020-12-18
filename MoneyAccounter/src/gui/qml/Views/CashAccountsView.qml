import QtQuick 2.0
import "qrc:/Delegates"
import "qrc:/Dialogs"

Item {
    id: cashAccViewItem

    Connections {
        target: middlewareQML // Указываем целевое соединение

        onSignalCashAccountLoaded : {
            listCashAccs.append({
                                    id: qmlProperty.idCashAcc,
                                    name: qmlProperty.nameCashAcc,
                                    description: qmlProperty.descriptionCashAcc,
                                    debtValue: qmlProperty.debtCashAcc,
                                    iconID: qmlProperty.iconIdCashAcc,
                                    iconPath: qmlProperty.iconPathCashAcc,
                                    typeID: qmlProperty.typeIdCashAcc,
                                    typeName: qmlProperty.typeNameCashAcc,
                                    typeDescription: qmlProperty.typeDescriptionCashAcc,
                                    typeIsIncludeDebt: qmlProperty.typeIsIncludeDebtCashAcc,
                                    typeIsIncludeRefund: qmlProperty.typeIsIncludeRefundCashAcc,
                                    typeIsIncludePrupose: qmlProperty.typeIsIncludePruposeCashAcc,
                                    colorIcon: qmlProperty.colorCashAcc,
                                    refund: qmlProperty.refundCashAcc,
                                    balance: qmlProperty.balanceCashAcc,
                                    purpose: qmlProperty.purpose,
                                    currencyID: qmlProperty.currencyIdCashAcc,
                                    currencyName: qmlProperty.currencyNameCashAcc,
                                    currencySymbol: qmlProperty.currencySymbolCashAcc,
                                    displayInExpenses: qmlProperty.displayInExpensesCashAcc,
                                    displayInOverallBalance: qmlProperty.displayInOverallBalanceCashAcc

                                })
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        ListView {
            id: cashAccList
            anchors {
                fill: parent
            }

            delegate: CashAccountsDelegate {}
            orientation: ListView.Vertical
            spacing: dp(10)
            cacheBuffer: 200
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            currentIndex: 1
            onCurrentIndexChanged: {

            }

            model: ListModel { id: listCashAccs }
        }
    }

    CashAccountDialog {
        id: cashAccDialog
    }

    function edit(index) {
        console.log(listCashAccs.get(index).name)
        cashAccDialog.setObject(listCashAccs.get(index))
        cashAccDialog.open()

        // Вызов диалогового окна на изменение
        // Через стэйт
    }

    function add() {
        // Вызов диалогового окна на добавление
    }
}
