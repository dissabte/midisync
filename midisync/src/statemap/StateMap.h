#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class Property;

class StateMap : public QObject
{
	Q_OBJECT

	friend class StateNode;

public:
	explicit StateMap(QObject* parent = nullptr);
	virtual ~StateMap();

	Q_INVOKABLE Property* getProperty(const QString& path);

private:
	Property* registerProperty(const QString& path, const QVariant& initialValue);

private:
	QMap<QString, Property*> _map;
};
