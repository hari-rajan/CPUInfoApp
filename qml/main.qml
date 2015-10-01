/**
  * Main QML. Object Heirarchy...
  * Window
  * |_ Scroll View
  *   |_ListView
  *     |_ListElements (CPUListModel.qml)
  * |_ Buttons
  * |_ Heading
  * |_ No Data TF
  */

import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import "models"

Window {
    id: mainWindowId
    visible: true
    width: 700
    height: 640
    title: "CPU Information"
    x:0
    y:0
    minimumHeight: height
    minimumWidth: width
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    color:"#f0f0f0"

    /**
      * Function that updates the list elements. Call from
      * C++ with key, value, and element position
      */
    function updateList(key, value, location, count)
    {
        listviewId.model.setProperty(location, "key", key);
        listviewId.model.setProperty(location, "value", value);
        var listcount = listviewId.count;

        var diff = listcount - count;
        console.log("updatelist " + diff);

        //remove extra listelements
        if (diff > 0)
        {
            while (listviewId.count - count > 0)
            {
                console.log (listviewId.count - count);
                listviewId.model.remove(listviewId.count-1, 1);
            }
        }
    }

    /**
      * Function to set button states. Call from
      * C++ to set button enable or disable states
      */
    function setButtonState(btn, state)
    {
        if (btn === "prevButton")
        {
            prevButtonId.enabled = state;
        }
        else if (btn === "nextButton")
        {
            nextButtonId.enabled = state;
        }
    }

    // Scroll View for vertical and horizontal scroll bars
    // Incase of data exceeds window boundaries
    ScrollView {
        id: scrollviewId
        objectName: "scrollview"
        x:parent.x+10
        y: 47
        width: 683
        height: 466
        antialiasing: true
        transformOrigin: Item.Center
        highlightOnFocus: true
        frameVisible: false

        ListView {
            id: listviewId
            objectName: "listview"
            x: parent.x
            y: parent.y
            height: 405
            highlightMoveDuration: 1
            highlightRangeMode: ListView.ApplyRange
            orientation: ListView.Vertical
            keyNavigationWraps: true
            interactive: false
            boundsBehavior: Flickable.StopAtBounds
            snapMode: ListView.SnapOneItem
            flickableDirection: Flickable.VerticalFlick
            anchors.bottomMargin: 11
            width: 690
            model: CPUListModel{}
            visible: true

            delegate: Text {
                text: key + ": " + value
                wrapMode: Text.WordWrap
            }
        }
    }

    // TextField for NoData display
    Text {
        id: noDataId
        objectName: "noData"
        x: 261
        y: 259
        width: 189
        height: 33
        text: qsTr("No Data")
        visible: false
        style: Text.Raised
        wrapMode: Text.WrapAnywhere
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 19
        color:"#545435"
    }

    // App Header
    Text {
        id: cpuNameHeading
        objectName: "cpuNameHeading"
        x: 0
        y: 8
        width: 697
        height: 20
        text: qsTr("Text Edit")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 18
        color:"#545435"
    }

    //Button click signal for C++ handling
    signal btnClick(string msg)

    Button {
        id: nextButtonId
        objectName: "nextButton"
        x: 407
        y: 604
        text: qsTr("Next Core")
        checkable: false
        property bool enabled
        enabled:true

        onClicked: {
            if (enabled == true)
            {
                mainWindowId.btnClick("right")
            }
        }
    }

    Button {
        id: prevButtonId
        objectName: "revButton"
        x: 221
        y: 604
        text: qsTr("Prev Core")
        checkable: false
        property bool enabled
        enabled:true

        onClicked: {
            if (enabled == true)
            {
                mainWindowId.btnClick("left");
            }
        }
    }
}
