#pragma once
#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Enemy : public Entity
{
public:
	static Enemy * create();

private:
	Enemy();
	~Enemy();
};

