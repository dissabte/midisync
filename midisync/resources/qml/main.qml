import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
	id: mainWindow
	title: "MIDI Sync"

	width: 268
	height: 300

	minimumWidth: 268
	minimumHeight: 300

	maximumWidth: 268
	maximumHeight: 300

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

	statusBar: StatusBar {
		RowLayout {
			anchors.fill: parent
			Label {
				text: "Not sending MBC"
			}
		}
	}
}
