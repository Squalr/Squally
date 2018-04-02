#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Beetle : public Enemy
{
public:
	static Beetle * create();

private:
	Beetle();
	~Beetle();
};
