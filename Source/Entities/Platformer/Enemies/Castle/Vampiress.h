#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Vampiress : public PlatformerEnemy
{
public:
	static Vampiress * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyVampiress;

private:
	Vampiress(ValueMap* initProperties);
	~Vampiress();
};
