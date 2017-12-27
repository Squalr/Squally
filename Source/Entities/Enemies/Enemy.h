#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"

using namespace cocos2d;

class Enemy : public Entity
{
public:
	static Enemy * create();

private:
	Enemy();
	~Enemy();
};

