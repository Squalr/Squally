#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DarkTiger : public PlatformerEnemy
{
public:
	static DarkTiger* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDarkTiger;

private:
	typedef PlatformerEnemy super;
	DarkTiger(cocos2d::ValueMap& initProperties);
	~DarkTiger();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
