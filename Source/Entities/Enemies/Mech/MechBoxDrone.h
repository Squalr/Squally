#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechBoxDrone : public Enemy
{
public:
	static MechBoxDrone * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMechBoxDrone;

private:
	MechBoxDrone(ValueMap* initProperties);
	~MechBoxDrone();
};
