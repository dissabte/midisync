#pragma once

#include <QObject>

#include "../model/DeviceModel.h"
#include "../statemap/StateMap.h"
#include "DeviceControl.h"
#include "HotPlugControl.h"

class Application : public QObject
{
	Q_OBJECT
	Q_PROPERTY(StateMap* stateMap READ stateMap NOTIFY stateMapChanged)
	Q_PROPERTY(DeviceModel* model READ model NOTIFY modelChanged)

public:
	explicit Application();
	virtual ~Application();

	StateMap* stateMap();
	DeviceModel* model();

signals:
	void stateMapChanged();
	void modelChanged();

private:
	StateMap       _stateMap;
	DeviceModel    _model;
	HotPlugControl _hotPlugControl;
	DeviceControl  _deviceControl;
};
