#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class OrcGrunt : public PlatformerEnemy
{
public:
	static OrcGrunt * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyOrcGrunt;

private:
	OrcGrunt(ValueMap* initProperties);
	~OrcGrunt();
};
