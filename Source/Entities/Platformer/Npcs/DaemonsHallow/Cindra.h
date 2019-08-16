#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Cindra : public PlatformerFriendly
{
public:
	static Cindra* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCindra;

private:
	typedef PlatformerFriendly super;
	Cindra(cocos2d::ValueMap& properties);
	~Cindra();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
