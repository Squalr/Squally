#pragma once
#include "Engine/Maps/MapLayer.h"

class Hud;

class Background : public MapLayer
{
public:
	static Background* create(cocos2d::ValueMap& initProperties, std::string name, cocos2d::Node* child);

	static const std::string MapKeyBackgroundType;

private:
	typedef MapLayer super;
	Background(cocos2d::ValueMap& properties, std::string name, Node* child);
	~Background();

	Hud* background;
};
