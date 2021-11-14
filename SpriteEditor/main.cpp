#include "spriteeditorvc.h"

#include "StencilTester.cpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	testPointerArray();
	QApplication a(argc, argv);
	SpriteEditorVC w;
	w.show();
	return a.exec();
}
