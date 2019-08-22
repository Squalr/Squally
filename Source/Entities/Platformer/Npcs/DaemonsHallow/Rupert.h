#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;

class Rupert : public PlatformerFriendly
{
public:
	static Rupert* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyRupert;

private:
	typedef PlatformerFriendly super;
	Rupert(cocos2d::ValueMap& properties);
	~Rupert();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
