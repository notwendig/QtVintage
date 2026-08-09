#ifndef _LED_PLUGIN_H_
#define _LED_PLUGIN_H_

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

class LEDPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	LEDPlugin(QObject* parent=0);

	QString name() const;
	QString group() const;
	QString toolTip() const;
	QString whatsThis() const;
	QString includeFile() const;
	QIcon icon() const;

	bool isContainer() const;

	QWidget *createWidget(QWidget *parent);
	void initialize(QDesignerFormEditorInterface *core);
	bool isInitialized() const;
private:
	bool initialized;
};

#endif
