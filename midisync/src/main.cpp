#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <smidi/MidiDeviceEnumerator.h>
#include "model/DeviceModel.h"
#include "model/Device.h"
#include "control/SyncControl.h"
#include "statemap/StateMap.h"
#include "statemap/Property.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	qmlRegisterType<Property>("MidiSync", 1, 0, "Property");

	DeviceModel model;

	StateMap stateMap;
	SyncControl control(model, &stateMap);

	//control.refreshDeviceList(); // intial device list update

	engine.rootContext()->setContextProperty("deviceModel", &model);
	engine.rootContext()->setContextProperty("stateMap", &stateMap);

	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	return app.exec();
}
