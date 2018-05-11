#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class FireElemental : public Enemy
{
public:
	static FireElemental * create();

private:
	FireElemental();
	~FireElemental();
};
