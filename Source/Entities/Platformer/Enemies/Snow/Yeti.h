#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Yeti : public PlatformerEnemy
{
public:
	static Yeti* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyYeti;

private:
	Yeti(ValueMap* initProperties);
	~Yeti();
};
