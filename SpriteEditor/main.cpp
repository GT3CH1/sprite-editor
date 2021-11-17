#include "spriteeditorvc.h"
#include "spriteeditormodel.h"
#include "JsonTest.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	saveTest();
	SpriteEditorVC w;
	w.show();
	return a.exec();
}
