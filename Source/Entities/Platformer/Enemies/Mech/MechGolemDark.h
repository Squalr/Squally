#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolemDark : public PlatformerEnemy
{
public:
	static MechGolemDark * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMechGolemDark;

private:
	MechGolemDark(ValueMap* initProperties);
	~MechGolemDark();
};
