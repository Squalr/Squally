#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonCleaver : public Enemy
{
public:
	static SkeletonCleaver * create();

	static const std::string KeyEnemySkeletonCleaver;

private:
	SkeletonCleaver();
	~SkeletonCleaver();
};
