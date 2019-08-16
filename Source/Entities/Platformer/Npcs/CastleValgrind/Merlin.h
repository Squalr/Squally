#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Merlin : public PlatformerFriendly
{
public:
	static Merlin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMerlin;

private:
	typedef PlatformerFriendly super;
	Merlin(cocos2d::ValueMap& properties);
	~Merlin();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
