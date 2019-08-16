#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Kringle : public PlatformerFriendly
{
public:
	static Kringle* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKringle;

private:
	typedef PlatformerFriendly super;
	Kringle(cocos2d::ValueMap& properties);
	~Kringle();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
