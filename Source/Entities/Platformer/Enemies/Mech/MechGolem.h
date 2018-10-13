#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolem : public PlatformerEnemy
{
public:
	static MechGolem * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMechGolem;

private:
	MechGolem(ValueMap* initProperties);
	~MechGolem();
};
