#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Godiva : public PlatformerFriendly
{
public:
	static Godiva* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGodiva;

private:
	typedef PlatformerFriendly super;
	Godiva(cocos2d::ValueMap& properties);
	~Godiva();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
