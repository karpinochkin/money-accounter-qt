import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.10
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.3
import QtGraphicalEffects 1.0
import "qrc:/Delegates"
import "qrc:/Models"
import "qrc:/Highlighters"

ApplicationWindow {
    id: main
    x: 0
    y: 0

    minimumWidth: main.dp(380)
    minimumHeight: main.dp(640)

    title: qsTr("Money Accounter")
    visible: true

    onClosing: {
        if (middlewareQML.isAndroid())
        {
            close.accepted = false
        }
    }

    Connections {
        target: middlewareQML

        onSignalErrorResponse: {
            errorSound.play()
            responseErrorMessage.title = qsTr("Ошибка")
            responseErrorMessage.text = qmlProperty.errorResponse
            responseErrorMessage.open()
        }
    }

    MessageDialog {
        id: responseErrorMessage
        title: "error"
        text: "error"
        onAccepted: {
            responseErrorMessage.close()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: backgroundColor
    }

    footer: Rectangle {
        height: main.height / 14
        width: main.width
        color: Qt.lighter(backgroundColor)

        ListView {
            id: tabsView
            anchors {
                top: parent.top
                topMargin: dp(5)
                bottom: parent.bottom
                bottomMargin: dp(5)
                right: parent.right
                rightMargin: dp(10)
                left: parent.left
                leftMargin: dp(5)
            }

            model: TabModel{}
            delegate: TabsDelegate {}
//            highlight: TabHighlighter{}
//            highlightFollowsCurrentItem: true
            orientation: ListView.Horizontal
            spacing: dp(10)
            interactive: false
            currentIndex: 1
            onCurrentIndexChanged: console.log(currentIndex)
        }
    }


    property int dpi: Screen.pixelDensity * 25.4
    property color backgroundColor: "#212d3b"

    function dp(x){
        if(dpi < 120) {
            return x; // Для обычного монитора компьютера
        } else if (dpi>350)
        {
            return x*(dpi/200)
        }
        else if (dpi>240)
        {
            return x*(dpi/200)
        }
        else if (dpi>200)
        {
            return x*(dpi/160)
        }
        else
        {
            return x*(dpi/120);
        }
    }

    property int previousIndexOfButtonTabs: 0
    function setCurrentTab(index)
    {

    }
}
