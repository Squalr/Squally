#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Sarude : public PlatformerFriendly
{
public:
	static Sarude* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySarude;

private:
	typedef PlatformerFriendly super;
	Sarude(cocos2d::ValueMap& properties);
	~Sarude();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
