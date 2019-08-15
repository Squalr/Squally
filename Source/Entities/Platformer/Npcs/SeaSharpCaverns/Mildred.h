#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Mildred : public PlatformerFriendly
{
public:
	static Mildred* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyMildred;

private:
	typedef PlatformerFriendly super;
	Mildred(cocos2d::ValueMap& initProperties);
	~Mildred();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
