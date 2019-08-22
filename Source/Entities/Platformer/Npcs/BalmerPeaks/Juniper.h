#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Juniper : public PlatformerFriendly
{
public:
	static Juniper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyJuniper;

private:
	typedef PlatformerFriendly super;
	Juniper(cocos2d::ValueMap& properties);
	~Juniper();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
