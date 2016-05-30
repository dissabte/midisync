#pragma once

#include <QObject>
#include <QString>
#include <QVariant>

class Property : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString path READ path)
	Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

public:
	explicit Property(QObject* parent = nullptr);
	explicit Property(QObject* parent, const QString& path, const QVariant& initialValue);
	virtual ~Property();

	QString path() const;

	QVariant value() const;
	void setValue(QVariant newValue);

signals:
	void valueChanged();

private:
	QString  _path;
	QVariant _value;
};
