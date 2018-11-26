#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class TikiGolem : public PlatformerEnemy
{
public:
	static TikiGolem* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyTikiGolem;

private:
	TikiGolem(ValueMap* initProperties);
	~TikiGolem();
};
