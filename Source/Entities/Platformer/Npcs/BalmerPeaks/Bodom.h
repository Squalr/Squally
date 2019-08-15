#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Bodom : public PlatformerFriendly
{
public:
	static Bodom* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyBodom;

private:
	typedef PlatformerFriendly super;
	Bodom(cocos2d::ValueMap& initProperties);
	~Bodom();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
