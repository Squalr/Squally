#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGuard : public PlatformerEnemy
{
public:
	static MechGuard * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMechGuard;

private:
	MechGuard(ValueMap* initProperties);
	~MechGuard();
};
