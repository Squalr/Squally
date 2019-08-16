#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Tinsel : public PlatformerFriendly
{
public:
	static Tinsel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTinsel;

private:
	typedef PlatformerFriendly super;
	Tinsel(cocos2d::ValueMap& properties);
	~Tinsel();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
