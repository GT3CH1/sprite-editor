#include "spriteeditorvc.h"
#include "spriteeditormodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SpriteEditorVC w;
	w.show();
	//saveTest();
	return a.exec();
}
