#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Thor : public PlatformerFriendly
{
public:
	static Thor* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyThor;

private:
	typedef PlatformerFriendly super;
	Thor(cocos2d::ValueMap& properties);
	~Thor();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
