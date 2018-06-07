import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item
    width: 800
    height: 600

    signal qmlSignal(string msg)
    property int score: 0

    Rectangle {
        width: 800
        height: 600
        color: "black"

        GridLayout {
            columns: 1
            anchors.centerIn: parent

            TextArea {
                text: "Are you sure you want to quit ?"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 10
                color: "black"
            }

            TextArea {
                text: "Your current score is : " + item.score
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 10
                color: "black"
            }

            GridLayout {
                columns: 2
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: qsTr("Cancel")
                    width: 100
                    onClicked: item.qmlSignal("CancelQuit")
                }

                Button {
                    text: qsTr("Confirm")
                    width: 100
                    onClicked: item.qmlSignal("ConfirmQuit")
                }
            }
        }
    }
}
