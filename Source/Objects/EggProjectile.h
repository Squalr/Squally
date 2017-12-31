#pragma once
#include "cocos2d.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class EggProjectile : public CollisionObject
{
public:
	static EggProjectile* create();

private:
	EggProjectile();
	~EggProjectile();
};
