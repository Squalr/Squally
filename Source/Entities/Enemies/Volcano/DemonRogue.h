#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonRogue : public Enemy
{
public:
	static DemonRogue * create();

private:
	DemonRogue();
	~DemonRogue();
};
