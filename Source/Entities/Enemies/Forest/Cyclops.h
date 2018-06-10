#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Cyclops : public Enemy
{
public:
	static Cyclops * create();

private:
	Cyclops();
	~Cyclops();
};
