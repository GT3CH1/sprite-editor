#include "spriteeditormodel.h"
#include <iostream>

int saveTest()
{
	SpriteEditorModel model;
	string filepath = "C:\\Users\\Kenzie Evans\\Documents\\University of Utah\\Fall 2021\\CS 3505\\A7";
	model.addFrame();
	model.getFramefromIndex(1).fill(Qt::blue);
	model.save(filepath, "save");
	std::cout << model.getFrameCount() << std::endl;

	SpriteEditorModel model2;
	model2.load(filepath, "test");
	std::cout << model2.getFrameCount() << std::endl;

	return 1;
}
