#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <smidi/MidiDeviceEnumerator.h>
#include "model/DeviceModel.h"
#include "model/Device.h"
#include "control/SyncControl.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	DeviceModel model;
	MidiDeviceEnumerator enumerator;
	SyncControl control(enumerator, model);

	// intial device list update
	control.refreshDeviceList();

	engine.rootContext()->setContextProperty("deviceModel", &model);
	engine.rootContext()->setContextProperty("controlLayer", &control);

	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	return app.exec();
}
