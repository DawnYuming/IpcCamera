import QtQuick 2.0

Rectangle {
    id: root

    property string title: "IPC CAMERA"
    property string version: "V1.0.0"

    visible: true
    color: "#003371"

    Row {
        anchors.leftMargin: 15
        anchors.left: root.left
        anchors.verticalCenter: parent.verticalCenter
        spacing: 5

        Image {
            source: "qrc:/res/image/ipc_camera_log.png"
            sourceSize.width: root.width * 0.8
            sourceSize.height: root.height * 0.8
        }

        Text {
            anchors.leftMargin: 30
            text: qsTr(title)
            font.pixelSize: 25
            color: "white"
        }

        Text {
            anchors.leftMargin: 30
            text: qsTr(version)
            font.pixelSize: 25
            color: "white"
        }
    }
}
