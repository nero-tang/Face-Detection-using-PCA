#include "appwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// Set Qt style to Fusion
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	appWindow w;
	w.show();
	return a.exec();
}
