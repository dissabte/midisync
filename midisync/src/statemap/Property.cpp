#include "Property.h"

Property::Property(QObject* parent)
    : QObject(parent)
{
}

Property::Property(QObject* parent, const QString& path, const QVariant& initialValue)
    : QObject(parent)
    , _path(path)
    , _value(initialValue)
{
}

Property::~Property()
{
}

QString Property::path() const
{
	return _path;
}

QVariant Property::value() const
{
	return _value;
}

void Property::setValue(QVariant newValue)
{
	if (_value != newValue)
	{
		_value = newValue;
		emit valueChanged();
	}
}
