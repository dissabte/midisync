#include "Device.h"

Device::Device(const QString& name)
    : _name(name)
{
}

QString Device::name() const
{
	return _name;
}

bool Device::operator==(const Device& other) const
{
	return _name == other._name;
}
