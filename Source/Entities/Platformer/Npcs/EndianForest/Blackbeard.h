#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Blackbeard : public PlatformerFriendly
{
public:
	static Blackbeard* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBlackbeard;

private:
	typedef PlatformerFriendly super;
	Blackbeard(cocos2d::ValueMap& initProperties);
	~Blackbeard();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
