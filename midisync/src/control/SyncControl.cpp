#include "SyncControl.h"
#include "../statemap/Property.h"
#include <QDebug>

SyncControl::SyncControl(DeviceModel& model, StateMap* stateMap)
    : StateNode(nullptr, stateMap, QStringLiteral("SyncControl"))
    , _model(model)
    , _enumerator()
{
	_pSelectedDeviceIndex = registerProperty("SelectedDeviceIndex", QVariant::fromValue(int()));
	_pSelectedBPM = registerProperty("SelectedBPM", QVariant::fromValue(float()));
	_pRefreshDeviceList = registerProperty("RefreshDeviceList", QVariant::fromValue(false));
	_pStartSync = registerProperty("StartSync", QVariant::fromValue(false));
	_pStopSync = registerProperty("StopSync", QVariant::fromValue(false));
	_pRestartSync = registerProperty("RestartSync", QVariant::fromValue(false));

	connect(_pRefreshDeviceList, &Property::valueChanged, this, &SyncControl::onRefreshDeviceList);
	connect(_pStartSync, &Property::valueChanged, this, &SyncControl::onStartSync);
	connect(_pStopSync, &Property::valueChanged, this, &SyncControl::onStopSync);
	connect(_pRestartSync, &Property::valueChanged, this, &SyncControl::onRestartSync);
}

SyncControl::~SyncControl()
{
}

void SyncControl::onRefreshDeviceList()
{
	if (_pRefreshDeviceList->value().toBool())
	{
		_enumerator.updateDeviceList();
		_model.clear();
		for (const std::string& deviceName : _enumerator.deviceNames())
		{
			emit _model.deviceAppeared(QString::fromUtf8(deviceName.c_str()));
		}
		_pRefreshDeviceList->setValue(false);
	}
}

void SyncControl::onStartSync()
{
	if (_pStartSync->value().toBool())
	{
		qDebug() << "START, DEVICE:" << _pSelectedDeviceIndex->value().toInt() << ", BPM:" << _pSelectedBPM->value().toFloat();
		_pStartSync->setValue(false);
	}
}

void SyncControl::onStopSync()
{
	if (_pStopSync->value().toBool())
	{
		qDebug() << "STOP, DEVICE:" << _pSelectedDeviceIndex->value().toInt();
		_pStopSync->setValue(false);
	}

}

void SyncControl::onRestartSync()
{
	if (_pRestartSync->value().toBool())
	{
		qDebug() << "RESTART, DEVICE:" << _pSelectedDeviceIndex->value().toInt() << ", BPM:" << _pSelectedBPM->value().toFloat();
		_pRestartSync->setValue(false);
	}
}
