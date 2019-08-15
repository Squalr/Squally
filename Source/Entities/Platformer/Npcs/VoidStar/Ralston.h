#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Ralston : public PlatformerFriendly
{
public:
	static Ralston* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRalston;

private:
	typedef PlatformerFriendly super;
	Ralston(cocos2d::ValueMap& initProperties);
	~Ralston();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
