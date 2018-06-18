#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGrunt : public Enemy
{
public:
	static GoblinGrunt * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinGrunt;

private:
	GoblinGrunt(ValueMap* initProperties);
	~GoblinGrunt();
};
