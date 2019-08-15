#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Rusty : public PlatformerFriendly
{
public:
	static Rusty* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRusty;

private:
	typedef PlatformerFriendly super;
	Rusty(cocos2d::ValueMap& initProperties);
	~Rusty();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
