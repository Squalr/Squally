#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGruntBoar : public PlatformerEnemy
{
public:
	static GoblinGruntBoar * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGoblinGruntBoar;

private:
	GoblinGruntBoar(ValueMap* initProperties);
	~GoblinGruntBoar();
};
