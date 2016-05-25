#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <smidi/MidiDeviceEnumerator.h>
#include "model/DeviceModel.h"
#include "model/Device.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	DeviceModel model;
	MidiDeviceEnumerator enumerator;
	for (const std::string& deviceName : enumerator.deviceNames())
	{
		model.deviceAppeared(QString::fromUtf8(deviceName.c_str()));
	}

	engine.rootContext()->setContextProperty("deviceModel", &model);

	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	return app.exec();
}
