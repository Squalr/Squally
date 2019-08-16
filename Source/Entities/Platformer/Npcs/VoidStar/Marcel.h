#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Marcel : public PlatformerFriendly
{
public:
	static Marcel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMarcel;

private:
	typedef PlatformerFriendly super;
	Marcel(cocos2d::ValueMap& properties);
	~Marcel();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
