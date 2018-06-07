import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item
    width: 800
    height: 600

    Rectangle {
        width: 800
        height: 600
        color: "black"

        GridLayout {
            columns: 1
            anchors.centerIn: parent

            Button {
                text: qsTr("Start Game")
            }
        }
    }
}
