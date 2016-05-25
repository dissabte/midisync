#pragma once

#include <QObject>
#include <smidi/MidiDeviceEnumerator.h>
#include "../model/DeviceModel.h"


class SyncControl : public QObject
{
	Q_OBJECT
public:
	explicit SyncControl(MidiDeviceEnumerator& enumerator, DeviceModel& model, QObject* parent = nullptr);
	virtual ~SyncControl();

signals:
	void refreshDeviceList();
	void startSync(int deviceIndex, float bpm);
	void stopSync(int deviceIndex, float bpm);
	void restartSync(int deviceIndex, float bpm);

public slots:
	void onRefreshDeviceList();

private:
	MidiDeviceEnumerator& _enumerator;
	DeviceModel& _model;
};
