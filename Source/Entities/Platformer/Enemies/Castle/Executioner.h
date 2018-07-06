#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Executioner : public PlatformerEnemy
{
public:
	static Executioner * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyExecutioner;

private:
	Executioner(ValueMap* initProperties);
	~Executioner();
};
