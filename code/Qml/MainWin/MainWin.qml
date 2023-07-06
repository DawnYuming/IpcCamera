import QtQuick 2.0
import "../common"
import "./common"
Window {
    id: root

    visible: true
    width: _window.screenWidth
    height: _window.screenHeight

    Image {
        width: root.width
        height: root.height
        smooth: true
        source: "qrc:/res/image/mainWin_backgraound.jpeg"
    }

    Column {
        id: title
        spacing: 10

        TitleBar {
            width: root.width
            height: root.height * 0.06
        }

        Menu {
            id: menu
            width: root.width
            height: root.height * 0.06
        }
    }

    Rectangle {
        visible: true
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        color: "transparent"
        border.color: "#44CEF6"
        radius: 20
    }
}
