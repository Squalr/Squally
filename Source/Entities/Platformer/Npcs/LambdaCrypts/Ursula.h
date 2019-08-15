#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Ursula : public PlatformerFriendly
{
public:
	static Ursula* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyUrsula;

private:
	typedef PlatformerFriendly super;
	Ursula(cocos2d::ValueMap& initProperties);
	~Ursula();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
