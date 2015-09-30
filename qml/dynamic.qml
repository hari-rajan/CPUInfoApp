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

    function updateList(key, value, location)
    {
        //console.log("update list called " + location);
        listviewId.model.setProperty(location, "key", key);
        listviewId.model.setProperty(location, "value", value);
    }

    function setButtonState(btn, state)
    {
        //console.log("button " + btn + " " + state);
        if (btn === "prevButton")
        {
            prevButtonId.enabled = state;
        }
        else if (btn === "nextButton")
        {
            nextButtonId.enabled = state;
        }
    }

    ScrollView {
        id: scrollviewId
        objectName: "scrollview"
        x:parent.x+10
        y: 47
        width: 683
        height: 466
        horizontalScrollBarPolicy: 0
        highlightOnFocus: true
        frameVisible: false

        ListView {
            id: listviewId
            objectName: "listview"
            height: 405
            anchors.leftMargin: 0
            anchors.topMargin: 36
            anchors.rightMargin: 2
            anchors.bottomMargin: 15
            width: 430
            model: CPUListModel{}
            visible: true
            delegate: Text {
                text: key + ": " + value
            }
        }
    }

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

