#include "spriteeditormodel.h"

int saveTest()
{
	SpriteEditorModel model;

	string filepath = "C:\\Users\\Kenzie Evans\\Documents\\University of Utah\\Fall 2021\\CS 3505\\A7";
	model.save(filepath, "save");

	return 1;
}
