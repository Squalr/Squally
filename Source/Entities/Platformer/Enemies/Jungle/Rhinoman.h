#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Rhinoman : public PlatformerEnemy
{
public:
	static Rhinoman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyRhinoman;

private:
	Rhinoman(ValueMap* initProperties);
	~Rhinoman();
};
