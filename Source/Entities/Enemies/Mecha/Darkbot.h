#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DarkBot : public Enemy
{
public:
	static DarkBot * create();

private:
	DarkBot();
	~DarkBot();
};
