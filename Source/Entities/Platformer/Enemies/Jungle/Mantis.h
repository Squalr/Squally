#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Mantis : public PlatformerEnemy
{
public:
	static Mantis * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMantis;

private:
	Mantis(ValueMap* initProperties);
	~Mantis();
};
