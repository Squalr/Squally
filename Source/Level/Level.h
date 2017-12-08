#pragma once
#include "cocos2d.h"
#include "../Entities/Player.h"

using namespace cocos2d;

class Level : public Node
{
public:
	Level();
	~Level();

protected:
	Player * player;
	Sprite* backGround;
};

