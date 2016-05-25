import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

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
				model: deviceModel
				textRole: "name"
				onAccepted: { }
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
				}

				Label {
					anchors.verticalCenter: bpmSlider.verticalCenter
					text: "" + bpmSlider.value
				}
			}

			Button {
				id: startSyncButton
				text: qsTr("Start")
				Layout.fillWidth: true
			}

			Button {
				id: stopSyncButton
				text: qsTr("Stop")
				Layout.fillWidth: true
			}

			Button {
				id: restartSyncButton
				text: qsTr("Restart")
				Layout.fillWidth: true
			}
		}
	}
}
