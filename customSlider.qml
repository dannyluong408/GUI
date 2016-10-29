import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Item {
    width: 400
    height: 400
    Slider {
        anchors.centerIn: parent
        style: SliderStyle {
            handle: Image {
                source: "http://icons.iconarchive.com/icons/custom-icon-design/pretty-office-9/256/square-icon.png"
                width: 14
                height: 14
            }
        }
    }
}
