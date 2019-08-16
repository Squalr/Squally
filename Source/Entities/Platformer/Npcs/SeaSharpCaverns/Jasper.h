#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Jasper : public PlatformerFriendly
{
public:
	static Jasper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyJasper;

private:
	typedef PlatformerFriendly super;
	Jasper(cocos2d::ValueMap& properties);
	~Jasper();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
