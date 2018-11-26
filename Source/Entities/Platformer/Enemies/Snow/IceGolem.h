#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class IceGolem : public PlatformerEnemy
{
public:
	static IceGolem* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyIceGolem;

private:
	IceGolem(ValueMap* initProperties);
	~IceGolem();
};
