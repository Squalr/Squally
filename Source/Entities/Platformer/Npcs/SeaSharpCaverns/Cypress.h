#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Cypress : public PlatformerFriendly
{
public:
	static Cypress* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCypress;

private:
	typedef PlatformerFriendly super;
	Cypress(cocos2d::ValueMap& properties);
	~Cypress();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
