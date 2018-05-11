#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class TikiGolem : public Enemy
{
public:
	static TikiGolem * create();

private:
	TikiGolem();
	~TikiGolem();
};
