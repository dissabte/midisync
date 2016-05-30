#include "StateNode.h"
#include "StateMap.h"
#include "Property.h"

const QString slash = QStringLiteral("/");

StateNode::StateNode(StateNode* parent, StateMap* stateMap, const QString& name)
    : QObject(parent)
    , _stateMap(stateMap)
{
	setObjectName(name);
}

StateNode::~StateNode()
{
}

StateMap*StateNode::stateMap() const
{
	return _stateMap;
}

Property* StateNode::registerProperty(const QString& propertyName, const QVariant& initialValue)
{
	Property* result = nullptr;
	if (_stateMap)
	{
		const QString propertyFullName = path() + slash + propertyName;
		result = _stateMap->registerProperty(propertyFullName, initialValue);
		if (result)
		{
			result->setParent(this);
		}
	}
	return result;
}

QString StateNode::path() const
{
	QString combinedPath;
	const StateNode* currentNode = this;
	while (currentNode)
	{
		combinedPath.insert(0, slash + currentNode->objectName());
		currentNode = qobject_cast<StateNode*>(currentNode->parent());
	}
	return combinedPath;
}
