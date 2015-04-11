import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Brainwave UI")
    property int clientsCount: 0

    Connections {
                target: wsServer
                onNewConnection: {
                   //console.log(connectionsCount)
                   clientsCount = connectionsCount;
                  }
                onNewMessage: {
                    console.log("Message came in: ",messageString, "from: ",name);

                    messageArea.text +=  name + " says: " + messageString + "\n";
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
            x: 44
            y: 8
            //color: "#ffff00"
            text: qsTr("Clients: " + clientsCount)
        }
        Label {
            id: label1
            x: 44
            y: 28
            text: qsTr("Messages")
        }

        TextArea {
            id: messageArea
            x: 44
            y: 48
            width: 250
            height: 522
            readOnly: true
            wrapMode: TextEdit.WordWrap
        }

        Label {
            id: label2
            x: 305
            y: 16
            text: qsTr("Sensors:")
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
                meterColor: "orange"
                objectName: "attention1"
                level: 0
            }

            Meter {
                id:hb1
                meterColor: "darkorange"
                objectName: "hb1"
                level: 0
            }

            Meter {
                id:lb1
                meterColor: "yellow"
                objectName: "lb1"
                level: 0
            }

            Item {width:lb1.width; height: lb1.height}
            //2
            Meter {
                id:attention2
                meterColor: "orange"
                objectName: "attention2"
                level: 0
            }

            Meter {
                id:hb2
                meterColor: "darkorange"
                objectName: "hb2"
                level: 0
            }

            Meter {
                id:lb2
                meterColor: "yellow"
                objectName: "lb2"
                level: 0
            }

            Item {width:lb1.width; height: lb1.height}

            //3
            Meter {
                id:attention3
                meterColor: "orange"
                objectName: "attention3"
                level: 0
            }

            Meter {
                id:hb3
                meterColor: "darkorange"
                objectName: "hb3"
                level: 0
            }

            Meter {
                id:lb3
                meterColor: "yellow"
                objectName: "lb3"
                level: 0
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

        Meter {
            id: gsr1
            objectName: "skin1"
            meterColor: "darkred"
            animationDuration: 100
            x: 311
            y: 274
        }

        Meter {
            id: meter2
            objectName: "skin2"
            meterColor: "red"
            animationDuration: 100
            x: 435
            y: 275
        }

        Label {
            id: label3
            x: 311
            y: 431
            text: qsTr("GSR1")
        }

        Label {
            id: label4
            x: 435
            y: 431
            text: qsTr("GSR2")
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
