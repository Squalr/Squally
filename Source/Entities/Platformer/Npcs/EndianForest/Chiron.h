#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Chiron : public PlatformerFriendly
{
public:
	static Chiron* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyChiron;

private:
	typedef PlatformerFriendly super;
	Chiron(cocos2d::ValueMap& initProperties);
	~Chiron();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
