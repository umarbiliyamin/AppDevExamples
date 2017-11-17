import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function setTextFunction(messageText)
    {
        page1Page.textField1.text = messageText
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
            id: page1Page
            width: 640
            height: 336
        }

        Page {
            Label {
                id: label2
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    Connections{
        target: myClassItem
        //updateText()
        onUpdateText: {
            label2.text = "Slot reached."
        }
    }

    Button {
        id: button
        objectName: "myButton"
        x: 270
        y: 345
        text: qsTr("Button")
        function onButtonClickd(variant) {
            text = variant
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}

