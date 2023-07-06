import QtQuick 2.1

Rectangle {
    property string btMesg: ""
    property string btText: ""
    property string textColor: "#ffffff"
    property string pressedTextColor: textColor
    property string releaseTextColor: textColor
    property real   fontSize: 20
    property string buttonColor: "#00000000"
    property string pressedColor: buttonColor
    property string releaseColor: buttonColor
    property string btIcon: ""
    property string pressedIcon: btIcon
    property string releaseIcon: btIcon
    property string borderColor: textColor
    property string pressdBorderColor: borderColor
    property bool fullIcon: false
    property bool opacityValue: false
    property int btTextWeight: Font.Normal

    id: pushButton
    width: btIcon === "" ? 80 : btnImage.width; height: btIcon === "" ? 60 : btnImage.height
    color: mouseArea.pressed?pressedColor:releaseColor
    border.width: 0
    border.color: mouseArea.pressed?pressdBorderColor:borderColor
    focus : true
    signal clicked()
    signal clickedWithMesg(string mesg)
    signal pressed()
    signal release()
    signal doubleClicked()
    signal pressAndHold()

    Image {
        id: btnImage
        anchors.centerIn: parent
        source: mouseArea.pressed?pressedIcon:releaseIcon
    }

    Text {
        anchors.centerIn: parent
        text: btText
        font.weight: btTextWeight
        color: mouseArea.pressed?pressedTextColor:releaseTextColor
        font.pixelSize: fontSize
    }

    MouseArea{
        id : mouseArea
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent

        onClicked: {
            parent.clicked()
            parent.clickedWithMesg(btMesg)
        }

        onPressed: {
            parent.pressed(btMesg)
            opacityValue = true
        }

        onReleased: {
            parent.release()
            opacityValue = false
        }

        onDoubleClicked: {
            parent.doubleClicked()
        }

        onPressAndHold: {
            parent.pressAndHold()
        }
    }

    //-----------------------------------------------------------------------------
    onFullIconChanged: {
        if (fullIcon === true)
            btnImage.anchors.fill = pushButton
        else
            btnImage.anchors.centerIn = pushButton
    }
}
