#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DemonShaman : public PlatformerEnemy
{
public:
	static DemonShaman* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonShaman;

private:
	typedef PlatformerEnemy super;
	DemonShaman(cocos2d::ValueMap& initProperties);
	~DemonShaman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
