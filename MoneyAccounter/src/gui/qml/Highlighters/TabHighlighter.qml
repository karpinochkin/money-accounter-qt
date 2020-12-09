import QtQuick 2.0

Item {
    Rectangle {
        x: tabsView.currentItem.x - tabsView.currentItem.width/2
        y: tabsView.height/2

        height: tabsView.height/2
        width: tabsView.currentItem.width*2

        color: "#293a4c"
    }

    Rectangle {
        x: tabsView.currentItem.x + tabsView.currentItem.width

        width: tabsView.currentItem.width
        height: tabsView.height

        border.width: main.dp(4)
        border.color: "white"
        color: "white"
        radius: main.dp(20)
    }
}
