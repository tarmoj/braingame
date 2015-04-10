import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
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
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#74e107"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        anchors.fill: parent
        Label {
            id:clientsCountLabel
            x: 100
            y: 18
            //color: "#ffff00"
            text: qsTr("Clients: " + clientsCount)
        }
        Label {
            id: label1
            x: 100
            y: 38
            text: qsTr("Messages")
        }

        TextArea {
            id: messageArea
            x: 100
            y: 58
            width: 250
            height: 391
            readOnly: true
            wrapMode: TextEdit.WordWrap
        }

        Label {
            id: label2
            x: 363
            y: 38
            text: qsTr("Sensors:")
        }

        TextArea {
            id: sensorsArea
            x: 363
            y: 58
            width: 250
            height: 391
            readOnly: true
            wrapMode: TextEdit.WordWrap
        }
    }


}
