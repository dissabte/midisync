import QtQuick 2.5
import QtQuick.Controls 1.4
import MidiSync 1.0

Item {
	property Action quitApplicationAction: Action {
		text: qsTr("&Quit")
		tooltip: qsTr("Quit the application")
		shortcut: StandardKey.Quit
		onTriggered: Qt.quit();
	}

	property Action refreshDeviceListAction: Action {
		text: qsTr("&Refresh")
		tooltip: qsTr("Refresh device list")
		shortcut: "CTRL+R"
		onTriggered: app.stateMap.getProperty("/DeviceControl/RefreshDeviceList").value = true
	}

	property Action startSync: Action {
		tooltip: qsTr("Start sending MBC")
		shortcut: "CTRL+S"
		onTriggered: app.stateMap.getProperty("/DeviceControl/StartSync").value = true
		iconSource: "qrc:///img/play.png"
		enabled: !app.stateMap.getProperty("/DeviceControl/SyncIsStarted").value
	}

	property Action stopSync: Action {
		tooltip: qsTr("Stop sending MBC")
		shortcut: "CTRL+T"
		onTriggered: app.stateMap.getProperty("/DeviceControl/StopSync").value = true
		iconSource: "qrc:///img/stop.png"
		enabled: app.stateMap.getProperty("/DeviceControl/SyncIsStarted").value
	}
}
