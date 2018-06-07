#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechDog : public Enemy
{
public:
	static MechDog * create();

private:
	MechDog();
	~MechDog();
};
