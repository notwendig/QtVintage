
#include "LEDPlugin.h"
#include "LED.h"

#include <QtPlugin>

LEDPlugin::
LEDPlugin(QObject* parent) :
	QObject(parent),
	initialized(false)
{
}

QString LEDPlugin::
name() const
{
	return "LED";
}

QString LEDPlugin::
group() const
{
	return tr("Nadisoft");
}

QString LEDPlugin::
toolTip() const
{
	return tr("An LED");
}

QString LEDPlugin::
whatsThis() const
{
	return tr("An LED");
}

QString LEDPlugin::
includeFile() const
{
	return "LED.h";
}

QIcon LEDPlugin::
icon() const
{
	return QIcon(":/segment/led.png");
}

bool LEDPlugin::
isContainer() const
{
	return false;
}

QWidget * LEDPlugin::
createWidget(QWidget *parent)
{
	return new LED(parent);
}

void LEDPlugin::
initialize(QDesignerFormEditorInterface * /* core */)
{
	if (initialized)
		return;

	initialized = true;
}

bool LEDPlugin::
isInitialized() const
{
	return initialized;
}
