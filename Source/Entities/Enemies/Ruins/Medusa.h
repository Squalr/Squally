#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Medusa : public Enemy
{
public:
	static Medusa * create();

private:
	Medusa();
	~Medusa();
};
