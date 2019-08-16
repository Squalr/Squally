#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class KingRedsong : public PlatformerFriendly
{
public:
	static KingRedsong* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingRedsong;

private:
	typedef PlatformerFriendly super;
	KingRedsong(cocos2d::ValueMap& properties);
	~KingRedsong();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
