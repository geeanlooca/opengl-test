#include "opengltest.h"

opengltest::opengltest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.openGLWidget, &GLWidget::sendThroughput, this, &opengltest::showThroughput);
}

void opengltest::showThroughput(float MBps)
{
	this->ui.statusBar->showMessage(QString("Frametime: %1 ms").arg(QString::number(MBps)));
}
