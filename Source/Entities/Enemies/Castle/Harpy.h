#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Harpy : public Enemy
{
public:
	static Harpy * create();

private:
	Harpy();
	~Harpy();

	Sprite* sprite;
};
