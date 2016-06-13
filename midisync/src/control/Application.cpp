#include "Application.h"

#include <QQmlEngine>

Application::Application()
    : QObject(nullptr)
    , _stateMap(nullptr)
    , _model(nullptr)
    , _hotPlugControl(nullptr, &_stateMap)
    , _deviceControl(nullptr, &_stateMap, _model)
{
	QQmlEngine::setObjectOwnership(&_model, QQmlEngine::CppOwnership);
	QQmlEngine::setObjectOwnership(&_stateMap, QQmlEngine::CppOwnership);
	_deviceControl.refreshDeviceList();
}

Application::~Application()
{
}

StateMap* Application::stateMap()
{
	return &_stateMap;
}

DeviceModel* Application::model()
{
	return &_model;
}
