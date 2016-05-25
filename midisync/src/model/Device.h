#pragma once

#include <QString>

class Device
{
public:
	Device(const QString& name);

	QString name() const;

	bool operator==(const Device& other) const;

private:
	QString _name;
};
