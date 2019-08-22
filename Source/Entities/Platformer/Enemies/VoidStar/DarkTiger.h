#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class DarkTiger : public PlatformerEnemy
{
public:
	static DarkTiger* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDarkTiger;

private:
	typedef PlatformerEnemy super;
	DarkTiger(cocos2d::ValueMap& properties);
	~DarkTiger();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
