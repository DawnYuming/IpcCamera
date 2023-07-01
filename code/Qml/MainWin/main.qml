import QtQuick 2.6
//import MyModels 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "./Qml/common"

Window {
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")

    Text {
        id: name
        text: qsTr("Hello World")
    }
}
