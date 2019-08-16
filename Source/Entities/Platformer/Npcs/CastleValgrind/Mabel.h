#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Mabel : public PlatformerFriendly
{
public:
	static Mabel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMabel;

private:
	typedef PlatformerFriendly super;
	Mabel(cocos2d::ValueMap& properties);
	~Mabel();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
