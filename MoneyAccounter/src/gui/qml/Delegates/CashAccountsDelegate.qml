import QtQuick 2.0

Rectangle {
    id: cashAccountDelegateRect

    anchors {
        left: parent.left
        leftMargin: main.dp(20)
        right: parent.right
        rightMargin: main.dp(20)

    }
    color: "transparent"
    height: main.dp(50)

    Rectangle {
        id: cashAccIconRect
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            topMargin: main.dp(5)
            bottomMargin: main.dp(5)
            leftMargin: main.dp(10)
        }
        width: height
        color: colorIcon
        radius: main.dp(10)

        Image {
            source: "qrc:/"+iconPath
            width: parent.width / 2
            height: parent.height / 2
            anchors {
                centerIn: parent
            }
        }
    }

    Rectangle {
        id: cashAccTypeRect
        anchors {
            right: parent.right
            rightMargin: main.dp(10)
            top: parent.top
            topMargin: main.dp(3)
        }
        color: "transparent"
        width: parent.width / 4
        height: parent.height / 3

        Text {
            text: "• " + typeName
            anchors.fill: parent
            color: main.textColor
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
        }
    }

    Rectangle {
        id: cashAccDescRect
        anchors {
            right: parent.right
            rightMargin: main.dp(10)
            bottom: parent.bottom
            bottomMargin: main.dp(3)
        }
        width: parent.width / 4
        height: parent.height / 3
        color: "transparent"

        Text {
            text: description
            anchors.fill: parent
            color: Qt.darker(main.textColor)
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
        }
    }

    Rectangle {
        anchors {
            left: cashAccIconRect.right
            right: cashAccTypeRect.left
            top: parent.top
            topMargin: main.dp(5)
            bottomMargin: main.dp(5)
            bottom: parent.bottom
            leftMargin: main.dp(10)
        }
        color: "transparent"

        Rectangle {
            id: cashAccNameRect
            anchors {
                left: parent.left
                right: parent.right
            }
            height: parent.height / 2
            color: "transparent"
            Text {
                text: name
                anchors.fill: parent
                font.pixelSize: main.dp(15)
                color: main.textColor
                elide: Text.ElideRight
            }
        }

        Rectangle {
            id: cashAccBalanceRect
            anchors {
                left: parent.left
                right: parent.right
                top: cashAccNameRect.bottom
            }
            height: parent.height / 2
            color: "transparent"
            Text {
                text: balance + " " + currencySymbol
                anchors.fill: parent
                font.pixelSize: main.dp(20)
                color: main.textBlueColor
                elide: Text.ElideRight
            }
        }

    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right

            bottom: parent.bottom
        }
        color: Qt.darker(main.textColor)
        height: main.dp(1)
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            cashAccViewItem.edit(index)
        }
    }
}
