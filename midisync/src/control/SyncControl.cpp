#include "SyncControl.h"
#include "../statemap/Property.h"
#include <smidi/MidiDevice.h>
#include <smidi/MidiOutPort.h>
#include <QDebug>

SyncControl::SyncControl(DeviceModel& model, StateMap* stateMap)
    : StateNode(nullptr, stateMap, QStringLiteral("SyncControl"))
    , _model(model)
    , _enumerator()
{
	_pSelectedDeviceName = registerProperty("SelectedDeviceName", QVariant::fromValue(QString()));
	_pSelectedBPM = registerProperty("SelectedBPM", QVariant::fromValue(float()));
	_pRefreshDeviceList = registerProperty("RefreshDeviceList", QVariant::fromValue(false));
	_pStartSync = registerProperty("StartSync", QVariant::fromValue(false));
	_pStopSync = registerProperty("StopSync", QVariant::fromValue(false));
	_pResumeSync = registerProperty("ResumeSync", QVariant::fromValue(false));
	_pUpdateSync = registerProperty("UpdateSync", QVariant::fromValue(false));

	connect(_pRefreshDeviceList, &Property::valueChanged, this, &SyncControl::onRefreshDeviceList);
	connect(_pStartSync, &Property::valueChanged, this, &SyncControl::onStartSync);
	connect(_pStopSync, &Property::valueChanged, this, &SyncControl::onStopSync);
	connect(_pResumeSync, &Property::valueChanged, this, &SyncControl::onResumeSync);
	connect(_pUpdateSync, &Property::valueChanged, this, &SyncControl::onUpdateSync);
}

SyncControl::~SyncControl()
{
}

void SyncControl::refreshDeviceList()
{
	_enumerator.updateDeviceList();
	_model.clear();
	for (const std::string& deviceName : _enumerator.deviceNames())
	{
		emit _model.deviceAppeared(QString::fromUtf8(deviceName.c_str()));
	}
}

void SyncControl::onRefreshDeviceList()
{
	if (_pRefreshDeviceList->value().toBool())
	{
		refreshDeviceList();
		_pRefreshDeviceList->setValue(false);
	}
}

void SyncControl::onStartSync()
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
		}
		_pStartSync->setValue(false);
	}
}

void SyncControl::onStopSync()
{
	if (_pStopSync->value().toBool())
	{
		const QString deviceName = _pSelectedDeviceName->value().toString();
		std::shared_ptr<MidiDevice> device = _enumerator.createDevice(deviceName.toUtf8().constData());
		if (device && device->outputPorts().size() > 0)
		{
			MidiSync& sync = device->outputPorts()[0]->sync();
			sync.stopSync();
		}
		_pStopSync->setValue(false);
	}

}

void SyncControl::onResumeSync()
{
	if (_pResumeSync->value().toBool())
	{
		const QString deviceName = _pSelectedDeviceName->value().toString();
		std::shared_ptr<MidiDevice> device = _enumerator.createDevice(deviceName.toUtf8().constData());
		if (device && device->outputPorts().size() > 0)
		{
			MidiSync& sync = device->outputPorts()[0]->sync();
			sync.resumeSync();
		}
		_pResumeSync->setValue(false);
	}
}

void SyncControl::onUpdateSync()
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
