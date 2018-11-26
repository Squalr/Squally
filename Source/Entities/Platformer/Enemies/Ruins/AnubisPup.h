#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class AnubisPup : public PlatformerEnemy
{
public:
	static AnubisPup* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyAnubisPup;

private:
	AnubisPup(ValueMap* initProperties);
	~AnubisPup();
};
