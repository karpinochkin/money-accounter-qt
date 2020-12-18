import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Dialog {
    property QtObject object

    visible: false
    title: qsTr("Cash Account")
    width: parent.width / 1.1
    height: parent.height / 1.5

    contentItem: Rectangle {
        color: main.backgroundColor

        implicitWidth: parent.width
        implicitHeight: parent.height

        /// header
        Rectangle {
            id: headerCashAccDialog
            // header
            // здесь будут кнопки: удалить, отмена и принять
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            height: footer.height / 1.5
            color: Qt.lighter(backgroundColor)
        }

        /// title
        Rectangle {
            id: mainTitleCashAccRectangle
            // title
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: main.dp(5)
                rightMargin: main.dp(5)
                top: headerCashAccDialog.bottom
            }
            height: parent.height / 8 / 2
            color: "transparent"

            Rectangle {
                id: titleCashAccRect
                color: "transparent"
                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                }
                width: titleCashAcc.width

                Text {
                    id: titleCashAcc
                    text: qsTr("Cash Account")
                    font.pixelSize: main.dp(12)
                    anchors.left: parent.left
                    anchors.centerIn: parent
                    color: main.textColor
                }

            }
            Rectangle {
                color: "transparent"
                anchors.left: titleCashAccRect.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                Rectangle {
                    anchors {
                        left: parent.left
                        leftMargin: main.dp(5)
                        right: parent.right
                        rightMargin: main.dp(5)
                        verticalCenter: parent.verticalCenter
                    }
                    height: main.dp(1)
                }
            }
        }

        // icon and name edit block code
        Rectangle {
            id: iconAndNameCashAccEditRect
            color: "transparent"
            anchors {
                top: mainTitleCashAccRectangle.bottom
                left: parent.left
                right: parent.right
                leftMargin: main.dp(5)
                rightMargin: main.dp(5)
            }
            height: parent.height / 8


            // icon edit block code
            Rectangle {
                id: iconEditRect
                color: "transparent"
                anchors {
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                width: height

                // image icon
                Image {
                    id: iconEdit
                    source: ""
                    anchors.centerIn: parent
                    width: parent.width / 1.7
                    height: parent.height / 1.7
                }
            }

            // Name edit block code
            Rectangle {
                color: "transparent"
                anchors {
                    left: parent.left
                    right: iconEditRect.left
                    top: parent.top
                    bottom: parent.bottom
                }

                // title cash acc name edit
                Text {
                    id: titleNameCashAccRect
                    text: qsTr("Name")
                    font.pixelSize: main.dp(10)
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    color: Qt.darker(main.textColor)
                    height: parent.height / 3
                    verticalAlignment: Text.AlignBottom
                }

                // Enter cash acc name
                TextInput {
                    id: nameEdit
                    text: ""
                    color: main.textBlueColor
                    font.pixelSize: main.dp(12)
                    verticalAlignment: Text.AlignVCenter
                    clip: true
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: titleNameCashAccRect.bottom
                        bottom: parent.bottom
                    }

                }

                /// bottom line
                Rectangle {
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        right: parent.right
                    }
                    height: main.dp(1)
                    color: main.textBlueColor
                }
            }
        }

        // description and color edit block code
        Rectangle {
            /// ВЫНЕСТИ КОД ЭТОГО КВАДРАТА В ОТЕДЛЬНЫЙ ТИМПЛЕЙТ
        }

        Text {
            id: textItem
            text: ""
            color: "navy"
            anchors.centerIn: parent
        }
    }

    function setObject(item) {
        object = item
        update(item)
    }

    function update(item) {
        nameEdit.text = item.name
        iconEdit.source = "qrc:/" + item.iconPath
        textItem.text = item.id + " "
                + item.name + " "
                + item.description + " "
                +item.debtValue + " \n"
                + item.iconID + " "
                + item.iconPath + " \n"
                + item.typeID + " "
                + item.typeName + " "
                + item.typeDescription + " \n"
    }
}
//typeID: qmlProperty.typeIdCashAcc,
//typeName: qmlProperty.typeNameCashAcc,
//typeDescription: qmlProperty.typeDescriptionCashAcc,
//typeIsIncludeDebt: qmlProperty.typeIsIncludeDebtCashAcc,
//typeIsIncludeRefund: qmlProperty.typeIsIncludeRefundCashAcc,
//typeIsIncludePrupose: qmlProperty.typeIsIncludePruposeCashAcc,
//colorIcon: qmlProperty.colorCashAcc,
//refund: qmlProperty.refundCashAcc,
//balance: qmlProperty.balanceCashAcc,
//purpose: qmlProperty.purpose,
//currencyID: qmlProperty.currencyIdCashAcc,
//currencyName: qmlProperty.currencyNameCashAcc,
//currencySymbol: qmlProperty.currencySymbolCashAcc,
//displayInExpenses: qmlProperty.displayInExpensesCashAcc,
//displayInOverallBalance: qmlProperty.displayInOverallBalanceCashAcc
