import QtQuick 2.7

Page1Form {
    buttonProperty.onClicked: {
        console.log("Button Pressed. Entered text: " + textFieldProperty.text);
    }
}
