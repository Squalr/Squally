#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class TinyIceGolem : public Enemy
{
public:
	static TinyIceGolem * create();

private:
	TinyIceGolem();
	~TinyIceGolem();
};
