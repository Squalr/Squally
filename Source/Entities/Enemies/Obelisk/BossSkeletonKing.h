#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossSkeletonKing : public Enemy
{
public:
	static BossSkeletonKing * create();

private:
	BossSkeletonKing();
	~BossSkeletonKing();
};
