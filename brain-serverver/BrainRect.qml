import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: rectangle1
    width: 120
    height: 200
    color: "#cdf505"
    border.color: "#121a18"
    radius: 8
    border.width: 4
    property string name: "Performer 1"



    Label {id:title; x: 0; text:name ; anchors.top: parent.top; anchors.topMargin: 10; anchors.horizontalCenterOffset: 0; anchors.horizontalCenter: parent.horizontalCenter;horizontalAlignment: Text.AlignHCenter}

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: title.bottom

        columns: 3
        rows: 3
        spacing: 5

        Meter {
            id:attention
            color: "orange"
            objectName: "attention1"
            level: 0
        }

        Meter {
            id:hb
            color: "darkorange"
            objectName: "lb1"
            level: 0
        }

        Meter {
            id:lb
            color: "yellow"
            objectName: "attention1"
            level: 0
        }

        Text {text: qsTr("A") ;horizontalAlignment: Text.AlignHCenter}
        Text {text: qsTr("HB") ;horizontalAlignment: Text.AlignHCenter}
        Text {text: qsTr("LB") ;horizontalAlignment: Text.AlignHCenter}
    }

}

