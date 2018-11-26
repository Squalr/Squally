#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class OrcGrunt : public PlatformerEnemy
{
public:
	static OrcGrunt* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyOrcGrunt;

private:
	OrcGrunt(ValueMap* initProperties);
	~OrcGrunt();
};
