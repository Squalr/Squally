#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Gargoyle : public PlatformerEnemy
{
public:
	static Gargoyle * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGargoyle;

private:
	Gargoyle(ValueMap* initProperties);
	~Gargoyle();
};
