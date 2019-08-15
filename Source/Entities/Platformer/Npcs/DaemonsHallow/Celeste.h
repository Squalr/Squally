#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Celeste : public PlatformerFriendly
{
public:
	static Celeste* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCeleste;

private:
	typedef PlatformerFriendly super;
	Celeste(cocos2d::ValueMap& initProperties);
	~Celeste();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
