import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import MidiSync 1.0

Column {
	id: mainView
	spacing: 10

	property real minBpm: 30.0
	property real maxBpm: 250.0

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
				text: qsTr("MIDI Device:")
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

	Column {
		anchors {
			left: parent.left
			right: parent.right
		}

		Label {
			text: qsTr("BPM:")
		}

		Item {
			width: parent.width
			height: bpmSlider.height

			Slider {
				id: bpmSlider
				anchors {
					left: parent.left
					right: bpmLabel.left
					rightMargin: 6
				}

				value: 120.0
				stepSize: 1.0
				minimumValue: minBpm
				maximumValue: maxBpm
				property Property pSelectedBPM: app.stateMap.getProperty("/DeviceControl/SelectedBPM")
				property Property pUpdateSync: app.stateMap.getProperty("/DeviceControl/UpdateSync")
				onValueChanged: {
					pSelectedBPM.value = value;
					pUpdateSync.value = true;
				}
			}

			Label {
				id: bpmLabel
				anchors {
					right: parent.right
					verticalCenter: bpmSlider.verticalCenter
				}
				text: "" + bpmSlider.value
			}
		}

		Row {
			width: parent.width
			spacing: 3

			Button {
				id: startStopSyncButton
				width: parent.width / 2 - 1
				height: width / 3
				action: actions.startSync
			}

			Button {
				id: stopSyncButton
				width: parent.width / 2 - 2
				height: width / 3
				action: actions.stopSync
			}
		}
	}
}
