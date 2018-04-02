#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Reindeer : public Enemy
{
public:
	static Reindeer * create();

private:
	Reindeer();
	~Reindeer();
};
