#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class DemonSwordsman : public PlatformerEnemy
{
public:
	static DemonSwordsman* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyDemonSwordsman;

private:
	DemonSwordsman(ValueMap* initProperties);
	~DemonSwordsman();
};
