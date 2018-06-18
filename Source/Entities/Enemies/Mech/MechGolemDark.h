#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolemDark : public Enemy
{
public:
	static MechGolemDark * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMechGolemDark;

private:
	MechGolemDark(ValueMap* initProperties);
	~MechGolemDark();
};
