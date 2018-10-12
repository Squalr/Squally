#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Wraith : public PlatformerEnemy
{
public:
	static Wraith * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyWraith;

private:
	Wraith(ValueMap* initProperties);
	~Wraith();
};
