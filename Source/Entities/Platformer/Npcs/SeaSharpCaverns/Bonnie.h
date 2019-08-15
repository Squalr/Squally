#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Bonnie : public PlatformerFriendly
{
public:
	static Bonnie* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBonnie;

private:
	typedef PlatformerFriendly super;
	Bonnie(cocos2d::ValueMap& initProperties);
	~Bonnie();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
