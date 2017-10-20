#include "opengltest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	opengltest w;
	w.show();
	return a.exec();
}
