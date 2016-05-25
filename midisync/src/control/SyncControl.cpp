#include "SyncControl.h"

SyncControl::SyncControl(MidiDeviceEnumerator& enumerator, DeviceModel& model, QObject* parent)
    : QObject(parent)
    , _enumerator(enumerator)
    , _model(model)
{
	connect(this, &SyncControl::refreshDeviceList, this, &SyncControl::onRefreshDeviceList);
}

SyncControl::~SyncControl()
{
}

void SyncControl::onRefreshDeviceList()
{
	_enumerator.updateDeviceList();
	_model.clear();
	for (const std::string& deviceName : _enumerator.deviceNames())
	{
		emit _model.deviceAppeared(QString::fromUtf8(deviceName.c_str()));
	}
}
