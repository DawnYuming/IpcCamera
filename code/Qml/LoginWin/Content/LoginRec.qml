import QtQuick 2.0
import QtQuick.Controls 2.1
import "../../common"

Rectangle {
    id: root

    property string title: "IPC CAMERA"

    signal btnClicked()

    radius: 20
    color: "transparent"

    border {
        width: 2
        color: "#70f3ff"
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Rectangle {
            width: root.width * 0.9
            height: root.height * 0.2

            color: "transparent"

            Text {
                text: qsTr(title)
                font.pointSize: 40
                font.bold: true
                color: "white"
                anchors.centerIn: parent
            }
        }

        Column {
            spacing: 30
            anchors.horizontalCenter: parent.horizontalCenter

            Row {
                spacing: 30

                TextInputRec {
                    id: account
                    width: root.width * 0.6
                    height: root.height * 0.1
                    placeholderText: "账号"
                }
            }

            Row {
                spacing: 30
                TextInputRec {
                    id: passwd
                    width: root.width * 0.6
                    height: root.height * 0.1
                    placeholderText: "密码"
                }
            }
        }

        PushButton {
            width: root.width * 0.2
            height: root.height * 0.12
            color: "#44CEF6"
            radius: 20
            btText: "登陆"
            btTextWeight: Font.Medium
            textColor: "white"
            anchors.horizontalCenter: parent.horizontalCenter

            onPressed: {
                color = "#94CD97"
            }

            onRelease: {
                color = "#44CEF6"
            }

            onClicked: {
                btnClicked()
            }
        }
    }

    function getAccount()
    {
        var accountText = account.displayText
        return accountText
    }

    function getPasswd()
    {
        var passwdText = passwd.displayText
        return passwdText
    }
}
