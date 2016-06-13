#pragma once

#include "../statemap/StateNode.h"
#include <hotplug/HotPlugWatcher.h>

class HotPlugControl : public StateNode
{
	Q_OBJECT

public:
	explicit HotPlugControl(StateNode* parent, StateMap* stateMap);
	virtual ~HotPlugControl();

	void onUSBDeviceHotPluggedNotification(const HotPlugNotificationType& type, const HotPlugNotificationData& notification);

private:
	HotPlugWatcher _usbHotPlugWatcher;

	Property* _pUSBDevicesChanged;
};

