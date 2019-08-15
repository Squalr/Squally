#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Sarude : public PlatformerFriendly
{
public:
	static Sarude* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeySarude;

private:
	typedef PlatformerFriendly super;
	Sarude(cocos2d::ValueMap& initProperties);
	~Sarude();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
