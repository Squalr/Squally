#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Dudly : public PlatformerFriendly
{
public:
	static Dudly* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDudly;

private:
	typedef PlatformerFriendly super;
	Dudly(cocos2d::ValueMap& properties);
	~Dudly();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
