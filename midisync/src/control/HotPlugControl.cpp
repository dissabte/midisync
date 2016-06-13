#include "HotPlugControl.h"
#include "../statemap/Property.h"
#include <functional>

HotPlugControl::HotPlugControl(StateNode* parent, StateMap* stateMap)
    : StateNode(parent, stateMap, QStringLiteral("HotPlugControl"))
    , _usbHotPlugWatcher(HotPlugWatcher::USB)
{
	_pUSBDevicesChanged = registerProperty("USBDevicesChanged", QVariant::fromValue(false));
	_usbHotPlugWatcher.registerObserver(std::bind(&HotPlugControl::onUSBDeviceHotPluggedNotification, this, std::placeholders::_1, std::placeholders::_2));
}

HotPlugControl::~HotPlugControl()
{

}

void HotPlugControl::onUSBDeviceHotPluggedNotification(const HotPlugNotificationType& type, const HotPlugNotificationData& /*notification*/)
{
	switch(type)
	{
	case HotPlugNotificationType::DEVICE_ADDED:
	case HotPlugNotificationType::DEVICE_REMOVED:
		_pUSBDevicesChanged->setValue(true);
		break;
	default:
		break;
	}
}
