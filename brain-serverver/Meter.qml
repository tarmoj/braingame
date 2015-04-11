import QtQuick 2.0

Rectangle  {
    id: meterRect
    width: 25
    height: 150
    color: "transparent"
    border.color: "black"
    property color meterColor: border.color
    border.width: 4
    radius: 8
    property double level: 0
    property int animationDuration: 1000

     Behavior on level { PropertyAnimation { duration: animationDuration} }

//    Rectangle {
//        id: borderRect
//        anchors.fill: parent
//        border.color: color
//        border.width: 4
//        radius: 4
//        color: parent.color

//    }

    Rectangle {
        id: fillRect
        x: parent.border.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.border.width
        color: parent.meterColor
        width: parent.width-2*parent.border.width
        height: parent.level*parent.height
    }


}
