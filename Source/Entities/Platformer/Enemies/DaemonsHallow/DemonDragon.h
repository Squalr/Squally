#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonDragon : public PlatformerEnemy
{
public:
	static DemonDragon* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonDragon;

private:
	typedef PlatformerEnemy super;
	DemonDragon(cocos2d::ValueMap& initProperties);
	~DemonDragon();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
