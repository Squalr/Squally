#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Tyracius : public PlatformerFriendly
{
public:
	static Tyracius* deserialize(cocos2d::ValueMap& initProperties);

	cocos2d::Vec2 getAvatarFrameOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyTyracius;

private:
	typedef PlatformerFriendly super;
	Tyracius(cocos2d::ValueMap& initProperties);
	~Tyracius();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
