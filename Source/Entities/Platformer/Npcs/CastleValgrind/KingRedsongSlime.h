#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class KingRedsongSlime : public PlatformerFriendly
{
public:
	static KingRedsongSlime* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyKingRedsongSlime;

private:
	typedef PlatformerFriendly super;
	KingRedsongSlime(cocos2d::ValueMap& initProperties);
	~KingRedsongSlime();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
