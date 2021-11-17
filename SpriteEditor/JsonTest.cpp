#include "spriteeditormodel.h"
#include <iostream>

int saveTest()
{
	SpriteEditorModel model;
	string filepath = "C:\\Users\\Kenzie Evans\\Documents\\University of Utah\\Fall 2021\\CS 3505\\A7";
	model.save(filepath, "save");

	SpriteEditorModel model2;
	model2.load(filepath, "save");

	return 1;
}
