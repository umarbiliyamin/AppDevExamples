import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: window

    Connections{
        target: cppTicker
        onTick:{
            window.title = qsTr("Hello Tick")
        }
        onValueUpdated:{
            generatedSeries.append(x,y);

            if(x > xAxis.max){
                xAxis.max = x
            }
            //retreiving the list data from the CustumTicker object
            cppTicker.dataItems.forEach(function(element) {
                console.log(element.value1);
            });
        }
    }

    //https://doc.qt.io/qt-5/qtcharts-qmlmodule.html
    ChartView {
        anchors.top: rowLayout.bottom
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

       ValueAxis{
           id: xAxis
           min: 0
           max: 10
       }

       ValueAxis{
        id: yAxis
        min: -1.1
        max: 1.1
       }

        LineSeries{
            name: "First Series"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
        }

        LineSeries{
            axisX: xAxis
            axisY: yAxis
            id: generatedSeries
            name: "Generated Series"
        }
    }

    //Three button example
    RowLayout {
        id: rowLayout
        height: 100
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Button {
            id: button
            text: qsTr("Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: button1
            text: qsTr("Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: button2
            text: qsTr("Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
