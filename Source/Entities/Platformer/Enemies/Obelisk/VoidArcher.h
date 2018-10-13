#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class VoidArcher : public PlatformerEnemy
{
public:
	static VoidArcher * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyVoidArcher;

private:
	VoidArcher(ValueMap* initProperties);
	~VoidArcher();
};
