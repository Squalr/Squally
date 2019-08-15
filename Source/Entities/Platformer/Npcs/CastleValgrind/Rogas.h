#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Rogas : public PlatformerFriendly
{
public:
	static Rogas* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRogas;

private:
	typedef PlatformerFriendly super;
	Rogas(cocos2d::ValueMap& initProperties);
	~Rogas();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
