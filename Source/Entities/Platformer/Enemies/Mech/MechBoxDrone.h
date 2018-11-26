#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class MechBoxDrone : public PlatformerEnemy
{
public:
	static MechBoxDrone* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMechBoxDrone;

private:
	MechBoxDrone(ValueMap* initProperties);
	~MechBoxDrone();
};
