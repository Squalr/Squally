#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechDog : public Enemy
{
public:
	static MechDog * create();

private:
	MechDog();
	~MechDog();
};
