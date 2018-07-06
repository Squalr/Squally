#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonGhost : public PlatformerEnemy
{
public:
	static DemonGhost * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonGhost;

private:
	DemonGhost(ValueMap* initProperties);
	~DemonGhost();
};
