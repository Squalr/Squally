#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolem : public Enemy
{
public:
	static MechGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMechGolem;

private:
	MechGolem(ValueMap* initProperties);
	~MechGolem();
};
