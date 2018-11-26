#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class PenguinGrunt : public PlatformerEnemy
{
public:
	static PenguinGrunt* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyPenguinGrunt;

private:
	PenguinGrunt(ValueMap* initProperties);
	~PenguinGrunt();
};
