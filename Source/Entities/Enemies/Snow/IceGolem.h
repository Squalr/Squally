#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class IceGolem : public Enemy
{
public:
	static IceGolem * create();

private:
	IceGolem();
	~IceGolem();
};
