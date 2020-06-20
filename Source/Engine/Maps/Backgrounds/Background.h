#pragma once
#include "Engine/Maps/GameObject.h"

class Hud;

class Background : public GameObject
{
public:
	static Background* create(cocos2d::Node* child);

protected:
	Background(Node* child);
	virtual ~Background();

private:
	typedef GameObject super;

	Hud* background;
};
