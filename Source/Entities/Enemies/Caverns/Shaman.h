#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Shaman : public Enemy
{
public:
	static Shaman * create();

private:
	Shaman();
	~Shaman();
};
