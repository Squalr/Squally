#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class PrincessNebea : public PlatformerFriendly
{
public:
	static PrincessNebea* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyPrincessNebea;

private:
	typedef PlatformerFriendly super;
	PrincessNebea(cocos2d::ValueMap& properties);
	~PrincessNebea();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
