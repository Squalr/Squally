#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyReanimatedPig;

private:
	ReanimatedPig(ValueMap* initProperties);
	~ReanimatedPig();
};
