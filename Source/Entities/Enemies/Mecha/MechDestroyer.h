#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechDestroyer : public Enemy
{
public:
	static MechDestroyer * create();

private:
	MechDestroyer();
	~MechDestroyer();
};
