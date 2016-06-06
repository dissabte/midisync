#pragma once

#include <smidi/MidiDeviceEnumerator.h>
#include "../model/DeviceModel.h"
#include "../statemap/StateNode.h"


class DeviceControl : public StateNode
{
	Q_OBJECT
public:
	explicit DeviceControl(StateNode* parent, StateMap* stateMap, DeviceModel& model);
	virtual ~DeviceControl();

	void refreshDeviceList();

private slots:
	void onRefreshDeviceList();
	void onStartSync();
	void onStopSync();
	void onResumeSync();
	void onUpdateSync();

private:
	DeviceModel&         _model;
	MidiDeviceEnumerator _enumerator;

	Property* _pSelectedDeviceName;
	Property* _pSelectedBPM;
	Property* _pRefreshDeviceList;
	Property* _pStartSync;
	Property* _pStopSync;
	Property* _pResumeSync;
	Property* _pUpdateSync;
};