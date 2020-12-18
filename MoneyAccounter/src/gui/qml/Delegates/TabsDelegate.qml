import QtQuick 2.0

Component {
    id: tabDelegate
    Rectangle {
        id: tabDelegateRect
        anchors {
            top: parent.top
            bottom: parent.bottom
            topMargin: main.dp(2)
            bottomMargin: main.dp(2)
        }
        width: tabsView.width / 4 - dp(2)
        color: "transparent"

        Column {
            spacing: main.dp(3)
            Image {
                width: tabDelegateRect.width
                height: tabDelegateRect.height / 1.3 - main.dp(3)
                source: image
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: tabName
                text: name
                width: tabDelegateRect.width
                height: tabDelegateRect.height / 3
                color: main.textColor
                horizontalAlignment: Text.AlignHCenter
            }

        }


        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                main.setCurrentTab(index)
            }
        }
    }
}
