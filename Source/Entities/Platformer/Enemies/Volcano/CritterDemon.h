#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class CritterDemon : public PlatformerEnemy
{
public:
	static CritterDemon * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyCritterDemon;

private:
	CritterDemon(ValueMap* initProperties);
	~CritterDemon();
};
