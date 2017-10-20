#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_opengltest.h"

class opengltest : public QMainWindow
{
	Q_OBJECT

public:
	opengltest(QWidget *parent = Q_NULLPTR);

private:
	Ui::opengltestClass ui;
private slots:
	void showThroughput(float MBps);
};
