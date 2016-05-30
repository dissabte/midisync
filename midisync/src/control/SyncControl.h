#pragma once

#include <smidi/MidiDeviceEnumerator.h>
#include "../model/DeviceModel.h"
#include "../statemap/StateNode.h"


class SyncControl : public StateNode
{
	Q_OBJECT
public:
	explicit SyncControl(DeviceModel& model, StateMap* stateMap);
	virtual ~SyncControl();

private slots:
	void onRefreshDeviceList();
	void onStartSync();
	void onStopSync();
	void onRestartSync();

private:
	DeviceModel&         _model;
	MidiDeviceEnumerator _enumerator;

	Property* _pSelectedDeviceIndex;
	Property* _pSelectedBPM;
	Property* _pRefreshDeviceList;
	Property* _pStartSync;
	Property* _pStopSync;
	Property* _pRestartSync;
};
