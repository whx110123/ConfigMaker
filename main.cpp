#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.setWindowTitle(QString("点表制作工具V1.01   ") + QString("          作者：王洪星"));
	w.show();
	return a.exec();
}
