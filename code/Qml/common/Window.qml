import QtQuick 2.6

Rectangle {
    property string title

//    width: 800
//    height: 600
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
