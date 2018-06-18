#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinShaman : public Enemy
{
public:
	static GoblinShaman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinShaman;

private:
	GoblinShaman(ValueMap* initProperties);
	~GoblinShaman();
};
