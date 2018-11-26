#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class TigerMan : public PlatformerEnemy
{
public:
	static TigerMan* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyTigerMan;

private:
	TigerMan(ValueMap* initProperties);
	~TigerMan();
};
