#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Agnes : public PlatformerEnemy
{
public:
	static Agnes * deserialize(ValueMap* initProperties);

	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyEnemyAgnes;
	static const std::string KeyName;

private:
	Agnes(ValueMap* initProperties);
	~Agnes();
};
