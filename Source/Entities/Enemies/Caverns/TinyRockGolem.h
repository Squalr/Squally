#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class TinyRockGolem : public Enemy
{
public:
	static TinyRockGolem * create();

private:
	TinyRockGolem();
	~TinyRockGolem();
};
