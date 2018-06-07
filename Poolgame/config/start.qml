import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item
    width: 800
    height: 600
    property int highscore: 0

    signal qmlSignal(string msg)

    Rectangle {
        width: 800
        height: 600
        color: "black"

        GridLayout {
            columns: 1
            anchors.centerIn: parent

            TextArea {
                text: "Super Mega Awesome Pool !"
                color: "white"
                font.pointSize: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "Karthikeyan Balasubramanian"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "SID: 460123835"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 50
                color: "black"
            }

            TextArea {
                id: highscore
                text: "Highscore : " + item.highscore
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 50
                color: "black"
            }

            TextArea {
                text: "IN-GAME CONTROLS"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "R : Rewind"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "F : Fast Forward"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "M : Menu"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            TextArea {
                text: "Q : Quit"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 20
                color: "black"
            }

            Button {
                text: qsTr("Start Game")
                width: 100
                onClicked: item.qmlSignal("StartGame")
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
