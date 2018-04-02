#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonArcher : public Enemy
{
public:
	static SkeletonArcher * create();

private:
	SkeletonArcher();
	~SkeletonArcher();
};
