#include "StateMap.h"
#include "Property.h"

StateMap::StateMap(QObject* parent)
    : QObject(parent)
{
}

StateMap::~StateMap()
{
}

Property* StateMap::registerProperty(const QString& path, const QVariant& initialValue)
{
	Property* result = nullptr;
	if (!_map.contains(path))
	{
		result = new Property(nullptr, path, initialValue);
		_map.insert(path, result);
	}
	return result;
}

Property* StateMap::getProperty(const QString& path)
{
	Property* result = nullptr;
	if (_map.contains(path))
	{
		result = _map[path];
	}
	return result;
}
