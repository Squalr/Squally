#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Xenon : public PlatformerFriendly
{
public:
	static Xenon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyXenon;

private:
	typedef PlatformerFriendly super;
	Xenon(cocos2d::ValueMap& properties);
	~Xenon();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
