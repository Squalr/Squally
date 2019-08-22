#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Igneus : public PlatformerFriendly
{
public:
	static Igneus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyIgneus;

private:
	typedef PlatformerFriendly super;
	Igneus(cocos2d::ValueMap& properties);
	~Igneus();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
