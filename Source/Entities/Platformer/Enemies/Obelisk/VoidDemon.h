#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class VoidDemon : public PlatformerEnemy
{
public:
	static VoidDemon * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyVoidDemon;

private:
	VoidDemon(ValueMap* initProperties);
	~VoidDemon();
};
