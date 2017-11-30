import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: page
            Button {

                function changeText(){
                    text = "button"
                }

                id: mybutton
                text: "BUTTON"
                anchors.bottom: firstLable.top
                anchors.bottomMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter

                onClicked: {
                    firstLable.color = "blue"
                }

                onPressed: {
                    changeColor()
                }

                //event handler of the Button
                onReleased: {
                    //reaching the reference of our cpp class instance
                    asYouLike.myFunction(firstLable.text)
                }

            }

            Label {
                id: firstLable
                text: qsTr("First page")
                wrapMode: Text.NoWrap
                anchors.centerIn: parent
            }
        }
    }
}
