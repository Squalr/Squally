#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Vampiress : public PlatformerEnemy
{
public:
	static Vampiress* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyVampiress;

private:
	Vampiress(ValueMap* initProperties);
	~Vampiress();
};
