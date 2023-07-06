import QtQuick 2.6
import MyModels 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "./Content"
import "../../Qml/common"

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

    TitleBar {
        width: root.width
        height: root.height * 0.06
    }

    LoginRec {
        id: loginRec

        title: "IPC CAMERA"
        width: root.width * 0.55
        height: root.height * 0.5
        anchors.centerIn: parent

        onBtnClicked: {
            var account = getAccount()
            var passwd = getPasswd()

            var res = loginModel.login(account, passwd)
            if (res === LoginModel.UNKNOW) {
                tisDialog.setContent("账户或者密码错误")
                tisDialog.show()
            }
        }
    }

    TisDialog {
        id: tisDialog
        height: 30
        backgroundColor: "#ef7a82"
        textColor: "red"
        anchors.top: loginRec.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    LoginModel {
        id: loginModel
    }
}
