import QtQuick 2.0

Rectangle {
    id: cashAccountDelegateRect

    anchors {
        left: parent.left
        right: parent.right

    }
    color: "transparent"
    height: cashAccountTypeInfoRect.height + cashAccList.height + main.dp(20)

    Rectangle {
        id: cashAccountTypeInfoRect
        anchors {
            left: parent.left
            right: parent.right
        }
        height: main.dp(70)
        color: Qt.darker(main.backgroundColor)

        Text {
            id: cashAccountTypeName
            text: name
            color: main.textColor
            font.pixelSize: main.dp(15)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors {
                top: parent.top
                topMargin: main.dp(10)
                left: parent.left
                right: parent.right
            }
            height: parent.height / 2 - main.dp(10)
        }

        Text {
            id: cashAccountTypeDescription
            text: description
            color: Qt.darker(main.textColor)
            anchors {
                bottom: parent.bottom
                bottomMargin: main.dp(10)
                left: parent.left
                right: parent.right
            }

            font.pixelSize: main.dp(10)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            height: parent.height / 2 - main.dp(10)
        }
    }


    ListView {
        id: cashAccList
        width: parent.width
        height: contentHeight
        delegate: Rectangle {
            height: main.dp(10)
            width: main.dp(10)
            Text {
                text: id
            }
        }
        anchors {
            top: cashAccountTypeInfoRect.bottom
            topMargin: main.dp(10)
        }

        orientation: ListView.Vertical
        spacing: dp(10)
        cacheBuffer: 200
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        currentIndex: 1
        onCurrentIndexChanged: {

        }
        model: ListModel { id: listCashAccs}
    }
}
