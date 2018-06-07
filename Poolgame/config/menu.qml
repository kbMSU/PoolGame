import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item
    width: 800
    height: 600

    signal qmlSignal(string msg)

    Rectangle {
        width: 800
        height: 600
        color: "black"

        GridLayout {
            columns: 1
            anchors.centerIn: parent

            TextArea {
                text: "Menu"
                color: "white"
                font.pointSize: 30
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 50
                color: "black"
            }

            Button {
                text: qsTr("Reset Game")
                onClicked: item.qmlSignal("ResetGame")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Button {
                text: qsTr("Export State")
                onClicked: item.qmlSignal("ExportSave")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 200
                height: 50
                color: "black"
            }

            Button {
                text: qsTr("Back")
                onClicked: item.qmlSignal("BackMenu")
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
