#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Tyracius : public PlatformerFriendly
{
public:
	static Tyracius* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTyracius;

private:
	typedef PlatformerFriendly super;
	Tyracius(cocos2d::ValueMap& properties);
	~Tyracius();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
