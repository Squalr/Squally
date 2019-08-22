#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Celeste : public PlatformerFriendly
{
public:
	static Celeste* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyCeleste;

private:
	typedef PlatformerFriendly super;
	Celeste(cocos2d::ValueMap& properties);
	~Celeste();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
