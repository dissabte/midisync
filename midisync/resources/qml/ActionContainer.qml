import QtQuick 2.5
import QtQuick.Controls 1.4

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
		text: qsTr("&Start")
		tooltip: qsTr("Start sending MBC")
		shortcut: "CTRL+S"
		onTriggered: app.stateMap.getProperty("/DeviceControl/StartSync").value = true
	}

	property Action stopSync: Action {
		text: qsTr("S&top")
		tooltip: qsTr("Stop sending MBC")
		shortcut: "CTRL+T"
		onTriggered: app.stateMap.getProperty("/DeviceControl/StopSync").value = true
	}

	property Action resumeSync: Action {
		text: qsTr("R&esume")
		tooltip: qsTr("Resume sending MBC")
		shortcut: "CTRL+E"
		onTriggered: app.stateMap.getProperty("/DeviceControl/ResumeSync").value = true
	}
}
