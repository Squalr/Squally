#pragma once
#include "Engine/Maps/GameObject.h"

class Hud;

class Background : public GameObject
{
public:
	static Background* create(cocos2d::Node* child);

private:
	typedef GameObject super;
	Background(Node* child);
	~Background();

	Hud* background;
};
