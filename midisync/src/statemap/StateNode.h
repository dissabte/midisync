#pragma once

#include <QObject>
#include <QString>
#include <QSharedPointer>

class StateMap;
class Property;

class StateNode : public QObject
{
	Q_OBJECT

public:
	explicit StateNode(StateNode* parent, StateMap* stateMap, const QString& name);
	virtual ~StateNode();

	StateMap* stateMap() const;
	Property* registerProperty(const QString& path, const QVariant& initialValue);

private:
	QString path() const;

private:
	StateMap* _stateMap;
};
