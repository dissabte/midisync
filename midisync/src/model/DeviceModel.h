#include <QAbstractListModel>
#include <QModelIndex>
#include <QHash>

#include "Device.h"

class DeviceModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum MountRoles {
		NameRole = Qt::UserRole + 1,
	};

public:
	explicit DeviceModel(QObject* parent = 0);
	virtual ~DeviceModel() = default;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QHash<int, QByteArray> roleNames() const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
	void deviceAppeared(const QString& name);
	void deviceDisappeared(const QString& name);
	void clear();

public slots:
	void onDeviceAppeared(const QString& name);
	void onDeviceDisappeared(const QString& name);
	void onClear();

private:
	QList<Device> _devices;
	QHash<int, QByteArray> _roleNames;
};
