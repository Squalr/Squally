#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonWarrior : public Enemy
{
public:
	static SkeletonWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonWarrior;

private:
	SkeletonWarrior(ValueMap* initProperties);
	~SkeletonWarrior();
};
