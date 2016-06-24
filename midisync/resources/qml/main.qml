import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import MidiSync 1.0

ApplicationWindow {
	id: mainWindow
	title: "MIDI Sync"

	width: 268
	height: 210

	minimumWidth: width
	minimumHeight: height
	maximumWidth: minimumWidth
	maximumHeight: minimumHeight

	visible: true

	SystemPalette { id: systemPaletteActive; colorGroup: SystemPalette.Active }

	ActionContainer { id: actions }

	menuBar: MenuBar {
		Menu {
			title: qsTr("&File");
			MenuItem { action: actions.quitApplicationAction }
		}
		Menu {
			title: qsTr("&Device")
			MenuItem { action: actions.refreshDeviceListAction }
		}
	}

	MainView {
		anchors {
			fill: parent
			margins: 10
		}
	}

	property Property pSyncIsStarted: app.stateMap.getProperty("/DeviceControl/SyncIsStarted")
	property bool syncIsStarted: pSyncIsStarted ? pSyncIsStarted.value : false

	property Property pSelectedBPM: app.stateMap.getProperty("/DeviceControl/SelectedBPM")
	property real selectedBPM: pSelectedBPM ? pSelectedBPM.value : 0

	statusBar: StatusBar {
		RowLayout {
			anchors.fill: parent
			Label {
				text: {
					if (syncIsStarted) {
						"Sending MBC at " + selectedBPM;
					} else {
						"Not sending MBC"
					}
				}
			}
		}
	}
}
