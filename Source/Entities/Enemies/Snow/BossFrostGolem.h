#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossFrostGolem : public Enemy
{
public:
	static BossFrostGolem * create();

private:
	BossFrostGolem();
	~BossFrostGolem();
};
