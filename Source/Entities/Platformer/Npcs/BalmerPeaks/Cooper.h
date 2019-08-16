#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Cooper : public PlatformerFriendly
{
public:
	static Cooper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCooper;

private:
	typedef PlatformerFriendly super;
	Cooper(cocos2d::ValueMap& properties);
	~Cooper();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
