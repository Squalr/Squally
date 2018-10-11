#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class AnubisPup : public PlatformerEnemy
{
public:
	static AnubisPup * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAnubisPup;

private:
	AnubisPup(ValueMap* initProperties);
	~AnubisPup();
};
