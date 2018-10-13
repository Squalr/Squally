#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Asmodeus : public PlatformerEnemy
{
public:
	static Asmodeus * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyAsmodeus;

private:
	Asmodeus(ValueMap* initProperties);
	~Asmodeus();
};
