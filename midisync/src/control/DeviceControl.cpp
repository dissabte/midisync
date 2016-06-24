#include "DeviceControl.h"
#include "../statemap/Property.h"
#include "../statemap/StateMap.h"
#include <smidi/MidiDevice.h>
#include <smidi/MidiOutPort.h>

DeviceControl::DeviceControl(StateNode* parent, StateMap* stateMap, DeviceModel& model)
    : StateNode(parent, stateMap, QStringLiteral("DeviceControl"))
    , _model(model)
    , _enumerator()
{
	_pSelectedDeviceName = registerProperty("SelectedDeviceName", QVariant::fromValue(QString()));
	_pSelectedBPM = registerProperty("SelectedBPM", QVariant::fromValue(float()));
	_pRefreshDeviceList = registerProperty("RefreshDeviceList", QVariant::fromValue(false));
	_pStartSync = registerProperty("StartSync", QVariant::fromValue(false));
	_pStopSync = registerProperty("StopSync", QVariant::fromValue(false));
	_pUpdateSync = registerProperty("UpdateSync", QVariant::fromValue(false));

	_pSyncIsStarted = registerProperty("SyncIsStarted", QVariant::fromValue(false));

	connect(_pRefreshDeviceList, &Property::valueChanged, this, &DeviceControl::onRefreshDeviceList);
	connect(_pStartSync, &Property::valueChanged, this, &DeviceControl::onStartSync);
	connect(_pStopSync, &Property::valueChanged, this, &DeviceControl::onStopSync);
	connect(_pUpdateSync, &Property::valueChanged, this, &DeviceControl::onUpdateSync);

	_pUSBDevicesChanged = stateMap->getProperty("/HotPlugControl/USBDevicesChanged");
	connect(_pUSBDevicesChanged, &Property::valueChanged, this, &DeviceControl::onUSBDevicesChanged);
}

DeviceControl::~DeviceControl()
{
}

void DeviceControl::refreshDeviceList()
{
	_enumerator.updateDeviceList();
	_model.clear();
	for (const std::string& deviceName : _enumerator.deviceNames())
	{
		emit _model.deviceAppeared(QString::fromUtf8(deviceName.c_str()));
	}
}

void DeviceControl::onRefreshDeviceList()
{
	if (_pRefreshDeviceList->value().toBool())
	{
		refreshDeviceList();
		_pRefreshDeviceList->setValue(false);
	}
}

void DeviceControl::onStartSync()
{
	if (_pStartSync->value().toBool())
	{
		const QString deviceName = _pSelectedDeviceName->value().toString();
		const double bpm = static_cast<double>(_pSelectedBPM->value().toFloat());
		std::shared_ptr<MidiDevice> device = _enumerator.createDevice(deviceName.toUtf8().constData());
		if (device && device->outputPorts().size() > 0)
		{
			MidiSync& sync = device->outputPorts()[0]->sync();
			sync.startSync(bpm);
			_pSyncIsStarted->setValue(true);
		}
		_pStartSync->setValue(false);
	}
}

void DeviceControl::onStopSync()
{
	if (_pStopSync->value().toBool())
	{
		const QString deviceName = _pSelectedDeviceName->value().toString();
		std::shared_ptr<MidiDevice> device = _enumerator.createDevice(deviceName.toUtf8().constData());
		if (device && device->outputPorts().size() > 0)
		{
			MidiSync& sync = device->outputPorts()[0]->sync();
			sync.stopSync();
			_pSyncIsStarted->setValue(false);
		}
		_pStopSync->setValue(false);
	}

}

void DeviceControl::onUpdateSync()
{
	if (_pUpdateSync->value().toBool())
	{
		const QString deviceName = _pSelectedDeviceName->value().toString();
		const double bpm = static_cast<double>(_pSelectedBPM->value().toFloat());
		std::shared_ptr<MidiDevice> device = _enumerator.createDevice(deviceName.toUtf8().constData());
		if (device && device->outputPorts().size() > 0)
		{
			MidiSync& sync = device->outputPorts()[0]->sync();
			sync.changeSyncBpm(bpm);
		}
		_pUpdateSync->setValue(false);
	}
}

void DeviceControl::onUSBDevicesChanged()
{
	if (_pUSBDevicesChanged->value().toBool())
	{
		refreshDeviceList();
		_pUSBDevicesChanged->setValue(false);
	}
}
