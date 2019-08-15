#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Bancroft : public PlatformerFriendly
{
public:
	static Bancroft* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBancroft;

private:
	typedef PlatformerFriendly super;
	Bancroft(cocos2d::ValueMap& initProperties);
	~Bancroft();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
