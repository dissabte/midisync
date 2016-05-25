import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
	id: mainWindow
	title: "MIDI Sync"

	width: 268
	height: 268

	minimumWidth: 268
	minimumHeight: 268

	maximumWidth: 268
	maximumHeight: 268

	visible: true

	SystemPalette { id: systemPaletteActive; colorGroup: SystemPalette.Active }

	Action {
		id: quitApplicationAction
		text: qsTr("&Quit")
		tooltip: qsTr("Quit the application")
		shortcut: StandardKey.Quit
		onTriggered: Qt.quit();
	}

	Action {
		id: refreshDeviceListAction
		text: qsTr("&Refresh")
		tooltip: qsTr("Refresh device list")
		shortcut: "CTRL+R"
		onTriggered: controlLayer.refreshDeviceList();
	}

	menuBar: MenuBar {
		Menu {
			title: qsTr("&File");
			MenuItem { action: quitApplicationAction }
		}
		Menu {
			title: qsTr("&Device")
			MenuItem { action: refreshDeviceListAction }
		}
	}

	MainView {
		anchors {
			fill: parent
			margins: 10
		}
	}

	statusBar: StatusBar {
		RowLayout {
			anchors.fill: parent
			Label {
				text: "Not sending MBC"
			}
		}
	}
}
