import QtQuick 2.6

Rectangle {
    property string title

    width: _window.screenWidth
    height: _window.screenHeight

    color : "#ffffff"

    /*格式化鼠标点击区域*/
    MouseArea { anchors.fill: parent }

    function enterWin(){}
    function enterWinWithArgs(args){}
    function exitWin(){}
    function temperatureUnitChanged(){}

//    function getTr(name)
//    {
//        return configModel.getTr(name, configModel.language)
//    }
}
