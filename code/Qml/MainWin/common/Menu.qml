import QtQuick 2.0
import "../common"

Rectangle {
    id: root
    color: "transparent"

    Row {
        spacing: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        IconRec {
            iconUrl: "qrc:/res/image/user_icon.png"
        }

        IconRec {
            iconUrl: "qrc:/res/image/camera_icon.png"
        }

        IconRec {
            iconUrl: "qrc:/res/image/photo_icon.png"
        }

        IconRec {
            iconUrl: "qrc:/res/image/setting_icon.png"
        }
    }
}
