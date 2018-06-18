#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonMage : public Enemy
{
public:
	static SkeletonMage * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonMage;

private:
	SkeletonMage(ValueMap* initProperties);
	~SkeletonMage();
};
