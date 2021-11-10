#include "spriteeditorvc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SpriteEditorVC w;
	w.show();
	return a.exec();
}
