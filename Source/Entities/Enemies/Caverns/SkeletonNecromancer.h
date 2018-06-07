#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonNecromancer : public Enemy
{
public:
	static SkeletonNecromancer * create();

private:
	SkeletonNecromancer();
	~SkeletonNecromancer();
};
