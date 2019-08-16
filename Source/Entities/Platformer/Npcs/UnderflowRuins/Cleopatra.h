#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Cleopatra : public PlatformerFriendly
{
public:
	static Cleopatra* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCleopatra;

private:
	typedef PlatformerFriendly super;
	Cleopatra(cocos2d::ValueMap& properties);
	~Cleopatra();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
