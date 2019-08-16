#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Zeus : public PlatformerFriendly
{
public:
	static Zeus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyZeus;

private:
	typedef PlatformerFriendly super;
	Zeus(cocos2d::ValueMap& properties);
	~Zeus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
