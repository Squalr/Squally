#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class PurpleDino : public Enemy
{
public:
	static PurpleDino * create();

private:
	PurpleDino();
	~PurpleDino();
};
