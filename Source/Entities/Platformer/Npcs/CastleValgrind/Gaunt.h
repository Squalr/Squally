#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Gaunt : public PlatformerFriendly
{
public:
	static Gaunt* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGaunt;

private:
	typedef PlatformerFriendly super;
	Gaunt(cocos2d::ValueMap& properties);
	~Gaunt();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
