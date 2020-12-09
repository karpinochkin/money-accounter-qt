import QtQuick 2.0

ListModel {
    id: tabModel

    ListElement {
        name: qsTr("Счета")
        image: "qrc:/images/icons/1.png"
    }
    ListElement {
        name: qsTr("Категории")
        image: "qrc:/images/icons/2.png"
    }
    ListElement {
        name: qsTr("Операции")
        image: "qrc:/images/icons/3.png"
    }
    ListElement {
        name: qsTr("Обзор")
        image: "qrc:/images/icons/4.png"
    }
}
