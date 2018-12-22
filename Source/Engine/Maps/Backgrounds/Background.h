#pragma once
#include "Engine/Maps/SerializableLayer.h"

class Hud;

class Background : public SerializableLayer
{
public:
	static Background* create(cocos2d::ValueMap* initProperties, std::string name, cocos2d::Node* child);

private:
	Background(cocos2d::ValueMap* properties, std::string name, Node* child);
	~Background();

	Hud* background;
};
