#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonRogue : public Enemy
{
public:
	static DemonRogue * create();

private:
	DemonRogue();
	~DemonRogue();
};
