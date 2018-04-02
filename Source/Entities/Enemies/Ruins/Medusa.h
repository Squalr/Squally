#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Medusa : public Enemy
{
public:
	static Medusa * create();

private:
	Medusa();
	~Medusa();
};
