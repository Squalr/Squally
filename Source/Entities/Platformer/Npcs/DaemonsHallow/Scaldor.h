#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Scaldor : public PlatformerFriendly
{
public:
	static Scaldor* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyScaldor;

private:
	typedef PlatformerFriendly super;
	Scaldor(cocos2d::ValueMap& properties);
	~Scaldor();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
