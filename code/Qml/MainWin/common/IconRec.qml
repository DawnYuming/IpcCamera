import QtQuick 2.0

Rectangle {
    id: root

    property string iconUrl: ""

    signal btnClick()

    visible: true
    color: "#003371"
    height: 40
    width: height

    Image {
        sourceSize.height: 30
        sourceSize.width: 30
        source: iconUrl
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            btnClick()
        }
    }
}
