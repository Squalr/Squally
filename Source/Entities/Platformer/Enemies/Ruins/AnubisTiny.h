#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class AnubisTiny : public PlatformerEnemy
{
public:
	static AnubisTiny * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAnubisTiny;

private:
	AnubisTiny(ValueMap* initProperties);
	~AnubisTiny();
};
