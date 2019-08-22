#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Aspen : public PlatformerFriendly
{
public:
	static Aspen* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyAspen;

private:
	typedef PlatformerFriendly super;
	Aspen(cocos2d::ValueMap& properties);
	~Aspen();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
