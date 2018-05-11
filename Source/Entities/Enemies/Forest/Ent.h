#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Ent : public Enemy
{
public:
	static Ent * create();

private:
	Ent();
	~Ent();
};
