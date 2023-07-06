import QtQuick 2.0

Rectangle {
    id: root

    implicitWidth: content.width + 5
    visible: false

    property string textColor: "black"
    property string backgroundColor: "white"

    color: backgroundColor

    Text {
        id: content
        color: textColor
        text: qsTr("")
        anchors.centerIn: parent
    }

    Timer {
            id: timer;
            interval: 1300;
            repeat: false
            running: false
            triggeredOnStart: false
            onTriggered: {
                hide()
            }
        }

    function show() {
        root.visible = true
        timer.running = true
    }

    function hide() {
        root.visible = false
    }

    function setContent(text) {
        content.text = text
    }
}
