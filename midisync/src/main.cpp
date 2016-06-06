#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "statemap/Property.h"
#include "control/Application.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	qmlRegisterType<Property>("MidiSync", 1, 0, "Property");

	Application application;

	engine.rootContext()->setContextProperty("app", &application);
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	return app.exec();
}
