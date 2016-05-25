#include "DeviceModel.h"
#include "Device.h"

DeviceModel::DeviceModel(QObject* parent)
    : QAbstractListModel(parent)
{
	_roleNames[NameRole] = "name";

	connect(this, &DeviceModel::deviceAppeared, this, &DeviceModel::onDeviceAppeared);
	connect(this, &DeviceModel::deviceDisappeared, this, &DeviceModel::onDeviceDisappeared);
	connect(this, &DeviceModel::clear, this, &DeviceModel::onClear);
}

int DeviceModel::rowCount(const QModelIndex& parent) const
{
	return _devices.count();
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
	return _roleNames;
}

QVariant DeviceModel::data(const QModelIndex& index, int role) const
{
	if (index.row() >= 0 && index.row() < _devices.count())
	{
		const Device& device = _devices[index.row()];
		switch (role)
		{
		case NameRole:
			return device.name();
		default:
			break;
		}
	}
	return QVariant();
}

void DeviceModel::onDeviceAppeared(const QString& name)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	_devices << Device(name);
	endInsertRows();
}

void DeviceModel::onDeviceDisappeared(const QString& name)
{
	int rowIndex = 0;
	for (const Device& device : _devices)
	{
		if (device.name() == name)
		{
			beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
			_devices.removeOne(device);
			endRemoveRows();
			break;
		}
		++rowIndex;
	}
}

void DeviceModel::onClear()
{
	beginRemoveRows(QModelIndex(), 0, rowCount());
	_devices.clear();
	endRemoveRows();
}
