#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class MechDog : public PlatformerEnemy
{
public:
	static MechDog* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMechDog;

private:
	MechDog(ValueMap* initProperties);
	~MechDog();
};
