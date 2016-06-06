import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import MidiSync 1.0

Column {
	id: mainView
	spacing: 10

	property real minBpm: 30.0
	property real maxBpm: 350.0

	Row {
		id: deviceControls
		height: deviceSelectionControls.height
		width: parent.width
		spacing: 30

		Column {
			id: deviceSelectionControls
			width: parent.width
			spacing: 6

			Label {
				id: selectDeviceText
				text: qsTr("Select MIDI Device:")
			}

			ComboBox {
				id: selectDeviceCombobox
				anchors {
					left: parent.left
					right: parent.right
				}
				editable: false
				model: app.model
				textRole: "name"

				property Property selectedDeviceName: app.stateMap.getProperty("/DeviceControl/SelectedDeviceName")

				onCurrentTextChanged: { selectedDeviceName.value = currentText; }
			}
		}
	}

	GroupBox {
		title: "Sync"
		anchors {
			left: parent.left
			right: parent.right
		}

		ColumnLayout {
			spacing: 6
			anchors {
				left: parent.left
				right: parent.right
			}

			Label {
				text: qsTr("BPM:")
			}

			Row {
				spacing: 6

				Slider {
					id: bpmSlider
					value: 120.0
					stepSize: 1.0
					minimumValue: minBpm
					maximumValue: maxBpm
					property Property selectedBPM: app.stateMap.getProperty("/DeviceControl/SelectedBPM")
					property Property updateSync: app.stateMap.getProperty("/DeviceControl/UpdateSync")
					onValueChanged: {
						selectedBPM.value = value;
						updateSync.value = true;
					}
				}

				Label {
					anchors.verticalCenter: bpmSlider.verticalCenter
					text: "" + bpmSlider.value
				}
			}

			Button {
				id: startSyncButton
				Layout.fillWidth: true
				action: actions.startSync
			}

			Button {
				id: stopSyncButton
				Layout.fillWidth: true
				action: actions.stopSync
			}

			Button {
				id: resumeSyncButton
				Layout.fillWidth: true
				action: actions.resumeSync
			}
		}
	}
}
