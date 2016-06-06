#include "Application.h"

#include <QQmlEngine>

Application::Application()
    : QObject(nullptr)
    , _stateMap(this)
    , _model(this)
    , _deviceControl(nullptr, &_stateMap, _model)
{
	QQmlEngine::setObjectOwnership(&_model, QQmlEngine::CppOwnership);

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
