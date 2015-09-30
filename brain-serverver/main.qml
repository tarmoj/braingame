import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 860
    height: 720
    title: qsTr("Brainwave UI")
    property int clientsCount: 0
    property int fontsize: 14

    Connections {
                target: wsServer
                onNewConnection: {
                   //console.log("QML connections: ",connectionsCount)
                   clientsCount = connectionsCount;
                  }
                onNewMessage: {
                    console.log("Message came in: ",messageString, "from: ",name);

                    messageArea.text += "<b>" + name + " says:</b> " + messageString + "\n";
                    messageArea.cursorPosition = messageArea.length;

                }
                onForwardSensorValue: {
                    console.log("sensor:",sensor," value: ",value)
                    sensorsArea.text +=  sensor + " "+ value + "\n";
                    sensorsArea.cursorPosition = sensorsArea.length;

                }
              }



    Rectangle {
        id: rectangle1
        width: 800
        height: 600
        color: "#cdf505"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#cdf505"
            }

            GradientStop {
                position: 1
                color: "#21221e"
            }
        }
        anchors.fill: parent
        Label {
            id:clientsCountLabel
            x: 16
            y: 16
            text: "Csounders: "+clientsCount
            visible: true
            //color: "#ffff00"
            font.pointSize: fontsize
        }
        Label {
            id: label1
            x: 15
            y: 52
            text: qsTr("Messages")
            font.pointSize: fontsize
        }

        TextArea {
            id: messageArea
            textFormat: TextEdit.RichText
            x: 15
            y: 79
            width: 368
            height: 612
            readOnly: true
            wrapMode: TextEdit.WordWrap
            font.pointSize: 10
        }

        Label {
            id: label2
            x: 546
            y: 16
            text: qsTr("Sensors")
            font.bold: true
            font.pointSize: fontsize
        }

        Grid {

            anchors.top: messageArea.top
            anchors.left: messageArea.right
            anchors.leftMargin: 16

            columns: 11
            rows: 3
            spacing: 5
             // TODO: use repeater or similar. Now bad code.
            Meter {
                id:attention1
                meterColor: "#CD0000" // red, darker and darker red
                objectName: "attention1"
            }

            Meter {
                id:hb1
                meterColor: "#AE0000"
                objectName: "hb1"

            }

            Meter {
                id:lb1
                meterColor: "#8A0000"
                objectName: "lb1"

            }

            Item {width:lb1.width; height: lb1.height}
            //2
            Meter {
                id:attention2
                meterColor: "#CD0000"
                objectName: "attention2"

            }

            Meter {
                id:hb2
                meterColor: "#AE0000"
                objectName: "hb2"

            }

            Meter {
                id:lb2
                meterColor: "#8A0000"
                objectName: "lb2"

            }

            Item {width:lb1.width; height: lb1.height}

            //3
            Meter {
                id:attention3
                meterColor: "#CD0000"
                objectName: "attention3"

            }

            Meter {
                id:hb3
                meterColor: "#AE0000"
                objectName: "hb3"

            }

            Meter {
                id:lb3
                meterColor: "#8A0000"
                objectName: "lb3"

            }





            Text {text: qsTr("A1") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("HB1") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("LB1") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: " "}

            Text {text: qsTr("A2") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("HB2") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("LB1") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: " "}

            Text {text: qsTr("A3") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("HB3") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: qsTr("LB3") ;horizontalAlignment: Text.AlignHCenter}
            Text {text: " "}


        }


        Label {
            id: heartRate1
            objectName: "heart1"
            property double level: 0
            x: 492
            y: 500
            font.pointSize: 32
            font.bold: true
            color: Qt.rgba(0.1+level/150.0,0,0,1) // the higher the rate, the more red it gets
            horizontalAlignment: Text.AlignHCenter
            text: level.toFixed(0)
        }

        Label {
            id: heartRate2
            objectName: "heart2"
            property double level: 0
            x: 707
            y: 500
            font.pointSize: 32
            font.bold: true
            color: Qt.rgba(0.1+level/150.0,0,0,1) // the higher the rate, the more red it gets
            horizontalAlignment: Text.AlignHCenter
            text: level.toFixed(0)
        }

//        Meter { // for skind conductance
//            id: gsr1
//            objectName: "skin1"
//            meterColor: "#A10048"
//            animationDuration: 250
//            x: 493
//            y: 419
//        }

//        Meter {
//            id: gsr2
//            objectName: "skin2"
//            meterColor: "#740034"
//            animationDuration: 250
//            x: 725
//            y: 419
//        }

        Label {
            id: label3
            x: 413
            y: 517
            text: qsTr("Pulse 1")
            font.pointSize: 12
            font.bold: true
        }

        Label {
            id: label4
            x: 632
            y: 517
            text: qsTr("Pulse 2")
            font.bold: true
            font.pointSize: 12
        }

        Label {
            id: label5
            x: 399
            y: 52
            text: qsTr("Brain:")
            font.pointSize: 14
            font.italic: true
        }

        Label {
            id: label6
            x: 390
            y: 387
            text: qsTr("Heart rate:")
            font.pointSize: 14
            font.italic: true
        }

        Label {
            id: label7
            x: 427
            y: 350
            text: qsTr("Brain 1")
            font.bold: true
            font.pointSize: 12
        }

        Label {
            id: label8
            x: 596
            y: 350
            text: qsTr("Brain 2")
            font.bold: true
            font.pointSize: 12
        }

        Label {
            id: label9
            x: 750
            y: 350
            text: qsTr("Brain 3")
            font.pointSize: 12
            font.bold: true
        }

        /*
        BrainRect {
            id: brainRect1
            x: 306
            y: 54
            name: "Helena"


        }

        BrainRect {
            id: brainRect2
            x: 433
            y: 55
            name: "Taavi"
        }

        BrainRect {
            id: brainRect3
            x: 560
            y: 55
            name: "vambola";
            //attention.objectName : "attention3"
        }
    */
    }


}
