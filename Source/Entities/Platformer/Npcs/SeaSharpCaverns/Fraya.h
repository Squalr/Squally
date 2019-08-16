#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Fraya : public PlatformerFriendly
{
public:
	static Fraya* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyFraya;

private:
	typedef PlatformerFriendly super;
	Fraya(cocos2d::ValueMap& properties);
	~Fraya();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
